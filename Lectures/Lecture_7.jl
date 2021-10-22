md"""
# ЛЕКЦИЯ 7

Обобщённое программирование (продолжение)
Примеры проектирования на основе построения иерархии типов даннных
"""
#=
Когда-то раньше, возможно, была спроетирована функция try_move!, делающая шага в заданном направлени 
или делающая попытку обхода перегородки, и возвращающая true/false - в зависимости от успеха

Эта функция нам теперь понадобится.
=#
function try_move!(r::Robot,side::HorizonSide)::Bool
    ort_side = left(side)
    n=0
    while isborder(r,side)
        if !isborder(r,ort_side)
            move!(r,ort_side)
            n += 1
        else
            break
        end
    end
    if isborder(r,side)
        movements!(r,inverse(ort_side),n)
        return false
    end
    move!(r,side)
    while isborder(r,inverse(ort_side))
        move!(r,side)
    end
    movements!(r,inverse(ort_side),n)
    return true
end

md"""
## Полезная иерархия абстрактных типов

Рассмотрим следующую иерархию типов, которая позволит нам писать обобщенный код

AbstractRobot
|
|--AbsctractBorderRobot: movements!(::AbsctractBorderRobot,::HorisonSide),
|  |                     movements!(::AbsctractBorderRobot,::HorisonSide,Integer), 
|  |                     try_move!(::AbstractBorderRobot, ::HorizonSide)
|  |
|  |--PutmarkersRobot: try_move!(::PutmarkersRobot, ::HorizonSide)
|  |--ContmarkerRobot: try_move!(::PutmarkersRobot, ::HorizonSide) 
|  |--....
|
|--AbstractCoordRobot
|  |
|  |-CoordRobot
|
|--....
"""
#--------------------------- определение абстрактного типа (его интерфейса)
abstract type AbstractRobot end

import HorizonSideRobots: move!, isborder!, putmarker!, ismarker, temperature

move!(robot::AbstractRobot, side::HorizonSide) = move!(get(robot), side)
isborder(robot::AbstractRobot,  side::HorizonSide) = isborder(get(robot), side)
putmarker!(robot::AbstractRobot) = putmarker!(get(robot))
ismarker(robot::AbstractRobot) = ismarker(get(robot))
temperature(robot::AbstractRobot) = temperature(get(robot))


#------------------------------- определение абстрактного типа (его интерфейса)
abstract type AbstractBorderRobot <: AbstractRobot end

function movements!(robot::AbstractBorderRobot, side::HorizonSide)
    n = 0
    while try_move!(robot,side)
        n += 1
    end
    return n
end

function movements!(robot::AbstractBorderRobot, side::HorizonSide, num_steps::Integer)
    for _ in 1:num_steps
        try_move!(robot,side)
    end
end

try_move!(robot::AbstractBorderRobot,side::HorizonSide) = try_move!(get(robot), side)
# - здесь включать эту функцию в интерфейс данного типа было не обязательно, 
#   но такая функция обязательно должна быть у всех производных типов

#----------------------------------------------------
#=
К интерфейсу абстрактного типа AbstractRobot целесообразно добавить ещё и функцию snake,
перемещающую робота из юго-западного угла змейкой до упора по горизонотальным рядам

(в Джулии всегда есть возможность расширить интерфейс любого типа)
=#
function snake(robot::AbstractRobot) # - это обобщенная функция
    # Робот - в юго-западном углу
    side = Ost
    movements!(robot,side)
    while !isborder(Nord)
        move!(robot,Nord)
        side = inverse(side)
        movements!(robot,side)
    end
end

#=
Эта функция (как и любая другая функция, входящая в интерфейс абстрактного типа) является обобщенной,
т.е. какой конкретно будет исполняться код при ее вызове - это зависит от фактичиского типа
аргумента, с которым эта функция будет вызвана (тип фактического аргумента функции всегда конкретный, 
абстрактным он быть не может)
=#
#------------------------------------------

md"""
## Примеры решения задач с использованием обобщенного кода на основе разработанной иерархии абстрактных типов

Решение многих задач теперь можно свести фактически просто к проектирванию конкретного типа, производного
от некоторого абстрактного (из числа уже разработанных)

"""

#=
Пример 1

ДАНО: Робот - в произвольной клетке поля между внутренними прямоугольными перегродками
РЕЗУЛЬТАТ: Робот - в исходном положении, все поле замаркировано

Для решения этой задачи спректируем следующий конкретный тип: 
=#

struct PutmarkersRobot <: AbstractBorderRobot
    robot::Robot
end
#=
У каждого конкретного типа обязательно должен быть конструктор
Конструктор - это специальная функция (имя которой всегда совпадает с именем типа), икоторая нужна для того,
что бы создавть объекты данного типа и размещать их в памяти 

В данном случае предполагается, использовать конструктор "по умолчанию", который може использоваться, например,
так:

 r=PutmarkersRobot(Robot())
=#

get(robot::PutmarkerRobot) = robot.robot 
# - эта функция должна определятся для каждого конкретного типа, производного от AbstractRobot

function try_move!(robot::PunmmarkerRobot, side::HorizonSide)
    if try_move!(get(robot),side)
        putmarker!(robot)
    end
end
# - переопределение функции для конкретного типа (у абстрактного родительского типа такой функции могло и не быть) 

#------------------

# Тепереь можно уже написать следующую функцию, решающую нашу задачу

function mark_field(r::Robot)
    back_path = BackPath(r)
    #УТВ: Робот - в Ю-З углу
    putmarkers_robot=PutmarkersRobot(r)
    putmarker!(putmarkers_robot)
    snak(putmarkers_robot)

    movements!(r,West)
    movements!(r,Sud)
    #УТВ: Робот снова находится в Ю-З углу
    back!(r, back_path)
    #УТВ: Робот - в исходном положении
end

#---------------------------------------------
#=
Пример 2

ДАНО: Робот - в юго-западном углу поля с внутренними прямоугольными или линейными перегородками между котрыми
имеется некоторо количество поставленных маркеров
РЕЗУЛЬТАТ: функция должна вернуть число этих маркеров

Для решения этой задачи будет полезен следующий производный от AbstractBorderRobot конкретный тип
=#

struct CountmarkersRobot <: AbstractBorderRobot
    robot::Robot
    count::Int
    CounmarkersRobot(r,n=0) = new(r,n)
end

function try_move!(robot::CounmarkersRobot, side::HorizonSide)
    if try_move!(get(robot),side)
        if ismarker(robot)
            robot.count += 1
        end
    end
end

get_count(robot::CounmarkersRobot) = robot.count

#=
Тогда функция, решающая задачу, может выглядеть так:
=#

function count_markers(r::Robot)
    r=CounmarkersRobot(r)
    snake(r)
    return get_count(r)
end
    