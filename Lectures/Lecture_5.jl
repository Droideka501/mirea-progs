md"""
# ЛЕКЦИЯ 5

В конце предыдущей лекции был введен заголовок "Иерархия пользовательских типов". 
Начнем эту тему заново.

Прежде всего вспомним рассмотренный в прошлый раз пример пользовательского типа `Coord`

"""
mutable struct Coord
    x::Int
    y::Int
    Coord() = new(0,0) # - такой конструктор определен для удобства использования
    Coord(x::Int,y::Int) = new(x,y)
end

function move!(coord::Coord, side::HorizonSide)
    if side==Nord
        coord.y += 1
    elseif side==Sud
        coord.y -= 1
    elseif side==Ost
        coord.x += 1
    else #if side==West
        coord.x -= 1
    end
end

get_coord(coord::Coord) = (coord.x, coord.y)


md"""
## 1. Иерархия пользовательских типов

Для того чтобы получить Робота, который при своих перемещениях будет отслеживать свои координаты
потребуется  "скрестить" два типа:

Robot + Coord

T.к. оба типа являются конкретными, то сделать это можно следующими способами: путем композиции типов или путем
проектирования дополнительного абстрактного типа с последующим наследованием от него.

### Композиция типов

Следующая структура представляет собой композицию конкретного типа Robot и конкретного типа Coord:
"""
struct XYRobot
    robot::Robot
    coord::Coord
    XYRobot(r,(x::Integer,y::Integer))=new(r,Coord(x,y))
    XYRobot(r)=new(r,Coord())
end

md"""
Теперь остается определить интерфейс для этого типа:
"""

function move!(robot::XYRobot, side::HorizonSide)
    move!(robot.robot, side)
    move!(robot.coord, side)
end
isborder(robot::XYRobot,  side::HorizonSide) = isborder(robot.robot, side)
putmarker!(robot::XYRobot) = putmarker!(robot.robot)
ismarker(robot::XYRobot) = ismarker(robot.robot)
temperature(robot::XYRobot) = temperature(robot.robot)
get_coord(robot::XYRobot) = get_coord(robot.coord)

md"""
### Пример 1

ДАНО: Робот - в некоторой клетке неограниченного поля, на котором могут находится маркеры
РЕЗУЛЬТАТ: функция возвращает вектор, содержащий координаты клеток с маркером (относительно начального положения робота),
находящиеся в квадрате с центорм в клетке сроботом и со стороной равной заданному 2N+1 (N in {0,1,2,...})
"""

function coords_marcers!(r::Rrobot, N::Integer)
    xyrobot=XYRobot(r)
    if ismarker(xyrobot)
        marker_coords=[(0,0)]
    else
        marker_coords = NTuple{2,Int}[]
    end

    n=1 # сторона текущего квадрата (размер элемента спирали)
    side = Nord # начальное направление раскручивания спирали
    while # ... не вышли за пределы квадрата со стороной 2N+1
        for _ in 1:n
            move!(xyrobot, side)
            if ismarker(xyrobot)
                push!(marker_coords, get_coord(xyrobot))
            end
            side = left(side) # должна возвращать следующее против часов стрелки направление
            if side in (Sud,Nord)
                n+=1
            end
        end
        return marker_coords
    end

md"""
## Проектирование иерархии типов
"""
abstract type AbstractRobot 
end

import HorizonSideRobots

move!(robot::AbstractRobot, side::HorizonSide) = HorizonSideRobots.move!(get(robot), side)
isborder(robot::AbstractRobot,  side::HorizonSide) = HorizonSideRobots.isborder(get(robot), side)
putmarker!(robot::AbstractRobot) = HorizonSideRobots.putmarker!(get(robot))
ismarker(robot::AbstractRobot) = HorizonSideRobots.ismarker(get(robot))
temperature(robot::AbstractRobot) = HorizonSideRobots.temperature(get(robot))
get(robot::AbstractRobot) = nothing

#-----------------------------------------


mutable struct CoordRobot <: AbstractRobot
    robot::Robot
    coord::Coord
    CoordRobot(r,(x::Integer,y::Integer))=new(r,Coord(0,0))
    CoordRobot(r)=new(r,Coord())
end

get(robot::CoordRobot) = robot.robot

function move!(robot::CoordRobot, side::HorizonSide)
    move!(get(robot), side)
    move!(robot.coord, side)
end

#-------------------------------------------

abstract type AbstractCoordRobot <: AbstractRobot 
#coord::Coord - поле с таким именем предполагается у всех производных типов
end

function move!(robot::AbstractCoordRobot, side::HorizonSide)
    move!(get(robot), side)
    move!(robot.coord, side)
end

#------------------------------

struct CounterMarkersRobot <: AbstractCoordRobot 
    robot::Robot
    num_markers::Int
    CounterMarkersRobot(robot::Robot)=new(robot, if ismarker(robot) 1 else 0 end)
end

get(robot::CounterMarkersRobot)=robot.robot

function move!(robot::CounterMarkersRobot, side::HorizonSide)
    move!(get(robot), side)
    if ismarker(robot)
        robot.num_markers += 1
    end
end

#-------------------------------------------------------




