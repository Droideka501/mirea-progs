md"""
# ЛЕКЦИЯ 6
- Пользовательские типы
- Обобщенные функции
(продолжение темы)

Рассмотрим задачу

## Задача 1
ДАНО: Робот - в некоторой клетке поля
РЕЗУЛЬТАТ: Робот в исходном положении и все клетки поля промаркированы в шахматном порядке так,
что в клетке с Роботом стоит маркер.


Следуя технологии сверху-вниз, и воспользовавшись некоторым ранее уже написанным кодом, 
можем записать решение этой задачи в следующем виде.
"""

function chess_mark!(r)
    back_path = BackPath(r)
    #УТВ: Робот - в Ю-З углу
    
    chess_mark_from_sw!(r, iseven(num_steps(back_path)))
    #Поле промаркировано в шахматном порядке

    movements!(r,Sud)
    movements!(r,West)
    #УТВ: Робот снова находится в Ю-З углу
    back!(r, back_path)
    #УТВ: Робот - в исходном положении
end

num_steps(back_path::BackPath) = sum(back_path.path)

#-------------------------------------------------
md"""
Остаётся только реализовать функцию chess_mark_from_sw!, 
которая должна будет перремещать робота змейкой по горизонтальным рядам, и расставлять маркеры в 
шахматном порядке.

Для её реализации можно, например, ввести глобальнцю переменную flag::Bool, с тем чтобы при каждом 
перемещении робота на 1 шаг ее значение менялось на противоположное, а маркер ставился бы только при
условии, что flag == true

Хотя решение с использованием глобальной переменной следует признать не очень хорошим, и такие решения
следует избегать, но начнем всё же с этого варианта (плохого!).
"""

flag = true

function chess_mark_from_sw!(r, marker_sw::Bool)
    # Робот - в юго-западном углу

    global flag = marker_sw

    side = Ost
    mark_line!(r,side)
    while !isborder(r,Nord)
        move!(r,Nord); flag = !flag
        side = inverse(side)
        mark_line!(r, side)
    end
end

function mark_line!(r, side::HorizonSide)
    global flag
    if flag
        putmarker!(r)
    end
    putmarkers!(r, side)
end

function putmarkers!(r, side::HorizonSide)
    global flag
    while !isborder(r,side)
        move!(r,side); flag = !flag
        if flag
            putmarker!(r)
        end
    end
end

md"""
Вариант с использованием глобальной переменной плох тем, что в результате мы получили функции, которые между 
собой связаны через эту глобальную переменную в одно целое, их не возможно отлаживать и использовать 
независимо друг от друга.

Кроме того, нам пришлось изменить код ранее написанных функций, которые составляли нашу собственную библиотеку
полезных функций.

Но от всех этих неприятностей можно легко избавиться, если специально для решения данной задачи сначала 
спроектировать НОВОГО РОБОТА (новый пользовательский тип данных).
"""

#--------------------
mutable struct ChessRobot <: AbstractRobot
    robot::Robot
    flag::Bool
end

get(r::ChessRobot) = r.robot

function move!(r::ChessRobot, side::HorizonSide) 
    move!(get(r),side)
    r.flag = !r.flag
end

function putmarker!(r::ChessRobot)
    if r.flag
        putmarker!(get(r))
    end
end

#----------------------------------------------

md"""
Тогда следующая функция mark_from_sw!(r::Any) будет обобщенной, т.е. довольно универсалной,
с помощью которой можно будет и замаркировать все клетки поля, и клетки поля в шахматном порядке,
и, может быть, в каком-либо еще порядке.

Конкретный результат будет зависеть от фактического типа ее аргумента. 
Т.е. если аргументом будет робот типа Robot, то маркироваться будет все поле подряд,
если аргументом будет робот типа ChessRobot, то - в шахматном порядке. 
"""

function mark_from_sw!(r) # эта функция ОБОБЩЕННАЯ
    # Робот - в юго-западном углу
    side = Ost
    mark_line!(r,side)
    while !isborder(r,Nord)
        move!(r,Nord); flag = !flag
        side = inverse(side)
        mark_line!(r, side)
    end
end

function mark_line!(r, side::HorizonSide)
    putmarker!(r)
    putmarkers!(r, side)
end

function putmarkers!(r, side::HorizonSide)
    while !isborder(r,side)
        move!(r,side)
        putmarker!(r)
    end
end

#-------------------------------------
md"""

Вот так теперь полученным обобщенным кодом можно воспользоваться для решения задачи 1:
"""

function chess_mark!(r::Robot)
    back_path = BackPath(r)
    #УТВ: Робот - в Ю-З углу
    
    r = ChessRobot(r, iseven(num_steps(back_path)))
    mark_from_sw!(r)
    #Поле промаркировано в шахматном порядке

    movements!(r,Sud)
    movements!(r,West)
    #УТВ: Робот снова находится в Ю-З углу
    back!(r, back_path)
    #УТВ: Робот - в исходном положении
end

num_steps(back_path::BackPath) = sum(back_path.path)

md"""
Тот же самый обобщённый код можно будет использовать и в случае, если понадобится ставить маркеры 
каким-то ещё другим способом. Для этого понадобится только спроектировать робота специального типа 
(специальный тип данных).

## Задача 2
ДАНО: Робот - в некоторой клетке поля
РЕЗУЛЬТАТ: Робот в исходном положении и все клетки поля промаркированы в шахматном порядке так,
что в клетке с Роботом стоит маркер.
"""

mutable struct NChessRobot <: AbstractCoordRobot
    robot::Robot
    N::Int
    coord::Coord
    NChessRobot(r,N::Int) = new(r,N,Coord())
end


get(r::NChessRobot) = r.robot

function putmarker!(r::ChessRobot)
    x,y = get_coord(r.coord)
    x = x % (2*r.N)
    y = y  % (2*r.N)
    if x in (0:r.N-1) && y in (0:r.N-1) || x in (r.N:2*r.N-1) && y in (r.N:2*r.N-1) 
        putmarker!(get(r))
    end
end

md"""
## ЗАМЕЧАНИЕ
Фактически тип аргумента r разработанных нами обобщенных функций: mark_from_sw!, mark_line!, putmarkers!
есть тип Any.

Но это слишком широкий тип, и мы могли бы сузить допустимы тип, описав его как объединение
конкретного типа Robot и абстрактного типа AbstrsctRobot 
"""
function mark_from_sw!(r::Union{Robot,AbstractRobot}) # эта функция ОБОБЩЕННАЯ
    # Робот - в юго-западном углу
    side = Ost
    mark_line!(r,side)
    while !isborder(r,Nord)
        move!(r,Nord); flag = !flag
        side = inverse(side)
        mark_line!(r, side)
    end
end

function mark_line!(r::Union{Robot,AbstractRobot}, side::HorizonSide)
    putmarker!(r)
    putmarkers!(r, side)
end

function putmarkers!(r::Union{Robot,AbstractRobot}, side::HorizonSide)
    while !isborder(r,side)
        move!(r,side)
        putmarker!(r)
    end
end