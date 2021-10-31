md"""
Лекция 8

## Проектираование на основе построения иерархии типов, параметрические типы


В лекции 7 была рассмотрена следующая иерархию типов, позволившая нам писать обобщенный код:

AbstractRobot:
|                        move!(::AbstractCoordRobot, ::HorizonSide), 
|                        isborder(::AbstractCoordRobot, ::HorizonSide), 
|                        putmarker!(::AbstractCoordRobot), 
|                        ismarker(::AbstractCoordRobot), 
|                        temperature(::AbstractCoordRobot)
|                        
|                        snake(::AbstractCoordRobot, NTuple(2,HorizonSide))
|
|--AbsctractBorderRobot: movements!(::AbsctractBorderRobot, ::HorisonSide),
|  |                     movements!(::AbsctractBorderRobot, ::HorisonSide, ::Integer), 
|  |                          (предполагается наличие функции try_move!(::Robot, ::HorizonSide))
|  |
|  |--PutmarkersBorderRobot: try_move!(::PutmarkersBorderRobot, ::HorizonSide), get(::PutmarkerRobot)
|  |--CountmarkerBorderRobot: try_move!(::PutmarkersBorderRobot, ::HorizonSide), get(::CountmarkerRobot)
|  |--....
|
|-- AbstractCoordRobot: 
|  |                    get_coords(::AbstractCoordRobot), 
|  |                    move!(::AbstractCoordRobot, ::HorizonSide)
|  |
|  |- CoordRobot: 
|  |              get(::AbstractCoordRobot)
|  |              get_coords(::AbstractCoordRobot), move!(::AbstractCoordRobot, ::HorizonSide)
|
|--....


Допустим теперь, что при перемещении робота по полю с обходом перегородок понадобилось ещё и вычислять текущие
координаты робота. Например, допустим, что требуется не постчитать число маркеров на поле, а получить их 
координаты (например, записать в массив).

Как можно было бы поступить в таком случае?

Например, можно было бы спроектировать, следующий тип данных.

"""
struct CoordmarkersBorderRobot <: AbstractBorderRobot
    robot::Robot
    coord::Coord
    marker_coord::Vector{NTuple{2,Int}}
end

md"""
Пример создания объекта типа CoormarkersBorderRobot:
"""
r=Robot(animate=true)

r = CoormarkersBorderRobot(r, Coord(), Int[])

md"""

При этом, однако, пришлось бы фактически повторить определения функций 
    get_coords(::AbstractCoordRobot), move!(::AbstractCoordRobot, ::HorizonSide),
(уже имеющихся для типа AbstractCoordRobot) т.е.
"""
get_coord(robot::CoordmarkersBorderRobot) = get_coord(robot.coord) #...get_coord -???
function move!(robot::CoordmarkersBorderRobot, side::HorizonSide)
    move!(robot,side)
    move!(robot.coord, side)
end

md"""
И, конечно, при этом потребуется ещё переопределить и функцию try_move! следующим образом.
"""

function try_move!(robot::CoordmarkersBorderRobot, side::HorizonSide)
    try_move!(robot.robot, side)
    if ismarker(robot)
        push!(robot.marker_coord, get_coord(robot))
    end
end

md"""

Однако необходимости писать функции 
    get_coords(::CoordmarkersBorderRobot), move!(::CoordmarkersBorderRobot, ::HorizonSide),
(повторяя фактически опрделения одноименных функций для типа AbstractCoordRobot)    
можно было бы избежать, если бы вместо типа AbsctractBorderRobot нами был бы спроектирован соответствующий
параметрический тип.

Вот как это могло бы выглядеть.

#------------------------------------------------------

AbstractRobot:
|                        move!(::AbstractRobot, ::HorizonSide), 
|                        isborder(::AbstractRobot, ::HorizonSide), 
|                        putmarker!(::AbstractRobot), 
|                        ismarker(::AbstractRobot), 
|                        temperature(::AbstractRobot)
|
|--AbsctractBorderRobot{TypeRobot}: # - параметрический тип, где TypeRobot - это параметр этого типа
|  |                     movements!(::AbsctractBorderRobot{TypeRobot},::HorisonSide),
|  |                     movements!(::AbsctractBorderRobot{TypeRobot},::HorisonSide,Integer), 
|  |                     try_move!(::AbstractBorderRobot{TypeRobot}, ::HorizonSide)
|  |                     get(robot::AbsctractBorderRobot{TypeRobot}) = robot.robot # get(robot::Robot) = robot
|  |
|  |--PutmarkersBorderRobot{TypeRobot}: # - теперь это особая разновидность абстрактных типов (все параметрические типы - абстрактные, хотя и определяются как структура)
|  |                    try_move!(::PutmarkersBorderRobot{TypeRobot}, ::HorizonSide), 
|  |
|  |--CountmarkerBorderRobot: 
|  |                    try_move!(::CountmarkerBorderRobot, ::HorizonSide), 
|  |                    
|  |--....
|
|--AbstractCoordRobot 
|  |
|  |-CoordRobot{TypeRobot}:
|  |                    get(robot::CoordRobot{TypeRobot}) = robot.robot  #::Robot
|
|--PutmarkerRobot
|--CountmarkersRobot
|--....


get(robot::Robot) = robot # - теперь это необходимо доопределить
#------------------------------------------------------

"""

abstract type AbstracrBorderRobot{TypeRobot} <: AbstractRobot end

function movements!(robot::AbsctractBorderRobot{TypeRobot},side::HorisonSide)
    n=0
    while try_move!(get(robot), side)
        n+=1
    end
    return n
end

function movements!(robot::AbstractBorderRobot{TypeRobot}, side::HorizonSide, num_steps::Integer)
    for _ in 1:num_steps
        try_move!(get(robot), side)
    end
end

#----------------------------------------------
get(robot::Robot) = robot


#--------------------------------------------------------
struct CoordmarkersBorderRobot{TypeRobot} <: AbstractBorderRobot{TypeRobot}
    robot::TypeRobot
    markers_coord::Vector{NTuple{2,Int}}
end

get(robot::CoordmarkersBorderRobot{CoordRobot})=get(robot.robot)

function try_move!(robot::CoordmarkersBorderRobot{CoordRobot}, side::HorizonSide)
    try_move!(get(robot), side)
    if ismarker(robot)
        push!(robot.marker_coord, get_coord(robot))
    end
end

md"""
ЗАМЕЧАНИЕ

Если определен тип CoordRobot
то тип CoordmarkersBorderRobot{CoordRobot} будет конкретными

Но тип CoordmarkersBorderRobot{TypeRobot} будет абстрактным параметрическим типом (если TypeRobot - это неопределенный параметр).

В данном случае функции get и try_move! были определены для конкретного типа CoordmarkersBorderRobot{CoordRobot}
(т.е. эти функции являются узко специализированными, не являются обобщенными)
#-----------------------------------------------------

ПРИМЕРЫ СОЗДАНИЯ ОБЪЕКТОВ
"""
r = Robot()

r1 = CoordmarkersBorderRobot{Robot}(r, Int[]) 
# - r1 - на самом деле координаты не отслеживает
#        и поэтому для типа CoordmarkersBorderRobot{Robot} нами не была определена функция try_move
#        (как и функция get)
#   Но тем не менее создать объект r1 можно, но использовать его для наших целей не получится

r2 = CoordRobot(r) # по умолчанию устанавливаются нулевые начальные координаты

get(r2) #--> r2.robot (::Robot)

r3 = CoordmarkersBorderRobot{CoordRobot}(r2, Int[]) # - отслеживает координаты

get(r3) #--> get(r3.robot) --> r3.robot.robot (::Robot)

#--------------------------------------

md"""
В виду бесполезности типа CoordmarkersBorderRobot{Robot}, а также бесполезности всех остальных возможных подтипов
типа CoordmarkersBorderRobot{TypeRobot} за исключением типа
CoordmarkersBorderRobot{CoordRobot}
тип CoordmarkersBorderRobot не следовало делать параметрическим.

Правильно было бы сделать так.
"""

struct CoordmarkersBorderRobot <: AbstractBorderRobot{CoordRobot}
    robot::CoordRobot
    markers_coord::Vector{NTuple{2,Int}}
end

get(robot::CoordmarkersBorderRobot) = get(robot.robot)

function try_move!(robot::CoordmarkersBorderRobot, side::HorizonSide)
    try_move!(get(robot), side)
    if ismarker(robot)
        push!(robot.marker_coord, get_coord(robot))
    end
end

md"""
ЗАДАЧА
ДАНО: Робот - в юго-западном углу пояля, на котором имеются внутренние прямоугольные или прямолинейные перегородки
РЕЗУЛЬТАТ: Функция вернула массив с координатами замаркированных клеток
"""

function markers_coord(r::Robot)
    coord_roobot = CoordRobot(r)
    robot = CoordmarkersBorderRobot(coord_roobot, Int[])
    snake!(robot)
    return robot.markers_coord
end

md"""
Если определить ещё следующую функцию
"""

get_markers_coord(robot::CoordmarkersBorderRobot) = robot.markers_coord

md"""

и если при этом функция snake! возвращает ссылку на робота (принимает её и её же возвращает),
то определение функции markers_coord(::Robot) могло бы быть совсем кратким:
"""

markers_coord(r::Robot) = get_markers_coord(snake!(CoordmarkersBorderRobot(CoordRobot(r), Int[])))

md"""
Для удобства можно было бы также определить ещё один конструктор:
CoordmarkersBorderRobot(r::Robot) = CoordmarkersBorderRobot(CoordRobot(r), Int[]))

тогда определение markers_coord(::Robot) могло бы стать еще более лаконичным:
"""
markers_coord(r::Robot) = get_markers_coord(snake!(CoordmarkersBorderRobot(r))

md"""
Пример проектирования ещё одного типа
"""

struct PutmarkersBorderRobot{TypeRobot} <: AbstractBorderRobot{TypeRobot}
    robot::TypeRobot
end

md"""
Здесь, в отличие от CoormarkersBorderRobot тип PutmarkersBorderRobot{TypeRobot} определен как параметрический.

Это не лишено смысла, т.к. робот-постановщик маркеров можно быть реализован как на базе типа Robot, так и 
на базе какого-нибудь другого типа, например, - CoordRobot

При этом, например, функции get и try_move могут быть определены как обобщенные функции, так и как узкоспециализированные 
"""
get(robot::PutmarkersBorderRobot{TypeRobot}) where TypeRobot = get(robot.robot)

function try_move!(robot::PutmarkersBorderRobot{TypeRobot}, side::HorizonSide) where TypeRobot
    if try_move!(get(robot), side)
        putmarker!(robot)
    end
end

Так определенные функции будут обобщенными, поскольку тип аргумента PutmarkersBorderRobot{TypeRobot} является
 абстрактным: зависит от параметра TypeRobot. То, что TypeRobot - это параметр, а не имя какого-то ранее опрделенного
 типа (абстрактного или конкретного) указывается с помощью ключевого слова where.

Следующие определния являются определениями узкоспециализированных функций (не обобщенных)

get(robot::PutmarkersBorderRobot{Robot}) = get(robot.robot)

function try_move!(robot::PutmarkersBorderRobot{Robot}, side::HorizonSide)
    if try_move!(get(robot), side)
        putmarker!(robot)
    end
end

В отличие от сделанных выше определений обобщенных функций get, try_move!, такие определения потребовались 
для каждого фактического значения параметра TypeRobot.

md"""
# Элементы функционального программирования

## Функции - как объекты 1-го класса
"""
x = 0

s = sin  # <: Function 

md"""
Пусть, например, мы хотим перемещать робота в заданном направлении до тех пор, пока не наступит некоторое событие,
выраженное соответствующим условием.

Это реализуется следующей функцией:
"""

function movements!(condition::Function, r, side)
    n=0
    while !condition(r)
        move!(r,side)
        n+=1
    end
    return n
end

#Теперь эту функцию можно вызывать, например, так:

movements!(isborder, r, side)

md"""
## Анонимные функции
Анонимные функции представляют собой функциональные значения (<: Function) без имени
 (подобно тому, как бывают значения типа Int без имени)

Например:

condition = robot -> !isborder(robot) 

Здесь переменной condition присвоено некоторое функциональное значение (значение анонимной функции) 
"""

