"""
Library of custom function for HorizonSideRoots by Droideka501 \n
link to repository https://github.com/Droideka501/mirea-progs
"""

using Revise
using HorizonSideRobots
import HorizonSideRobots: move!, isborder, ismarker, putmarker!, temperature, HorizonSide


#------------------------------------------------------------#
"""
Structs

BackPath:
|               back!(::AbstractRobot, ::BackPath)
|               numSteps(::BackPath)

Robot
|
|--AbstactRobot: 
|               move!(::AbstractRobot, ::HorizonSide)
|               isborder(::AbstractCoordRobot, ::HorizonSide)
|               putmarker!(::AbstractCoordRobot)
|               ismarker(::AbstractCoordRobot)
|               temperature(::AbstractCoordRobot)
|
|

"""
#------------------------------------------------------------#

"""
moves the robot to `(side, side)` corner and create the array of direction\n
default sides = (Sud, Ost)
"""
struct BackPath
    sides::NTuple{2, HorizonSide}
    path::Vector{Int}

    function BackPath(robot, sides::NTuple{2,HorizonSide}=(Sud, Ost))
        local path=[]
        while !isborder(robot, sides[1]) || !isborder(robot, sides[2])
            for s in sides 
                push!(path, movesAndCounting!(robot, s))
            end
        end
        new(reverse(map(side -> reversSide(side), sides)), reverse(path))
    end
end

"""
returns the number of steps taken by the robot
"""
numSteps(back_path::BackPath)::Integer = sum(back_path.path)

"""
moves the robot to initial place
"""
function back!(robot, backpath::BackPath)
    i=1
    for n in backpath.path
        moves!(robot, backpath.sides[i], n)
        i = i%2 + 1
    end
end


"""

"""
function get_xy(back_path::BackPath)
    num_x, num_y = (0, 0)
    for i in 1:length(back_path.path)
        if iseven(i)
            num_y += back_path.path[i]
        else
            num_x += back_path.path[i]
        end
    end
    return (num_x, num_y)
end


#------------------------------------------------------------#

"""
coordinate structure\n
includes a function for changing coordinates and getting a tuple of coordinates
"""
mutable struct Coords
    x::Integer
    y::Integer
    Coords() = new(0, 0)
    Coords(x::Integer, y::Integer) = new(x, y)
end

"""
returns tuple of coordinates 
"""
get_xy(coord::Coords) = (coord.x, coord.y)

"""
changes coordinates depending of `side`
"""
function move!(coord::Coords, side::HorizonSide)
    if side==Nord
        coord.y -= 1
    elseif side==Sud
        coord.y += 1
    elseif side==Ost
        coord.x += 1
    else
        coord.x -= 1
    end
end

#------------------------------------------------------------#

"""
an abstract type of robot that is a wrapper for the type ::Robot
"""
abstract type AbstractRobot end

"""
returs the link to the robot\n
typeof(get_robot(::AbstactRobot)) -> ::Robot
"""
get_robot(robot::AbstractRobot) = robot.robot

"""
returs the field coordinates of the robot\n
if robot
typeof(get_coords(::AbstactRobot)) -> ::Coords
"""
function get_coords(robot::AbstractRobot)
    if :coords in fieldnames(typeof(robot))
        return robot.coords
    else
        return error("This robot has not field coords")
    end
end

"""
returs the field flag of the robot\n
typeof(get_coords(::AbstactRobot)) -> ::Boll
"""
function get_flag(robot::AbstractRobot)
    if :flag in fieldnames(typeof(robot))
        return robot.flag
    else
        return error("This robot has not field flag")
    end
end

"""
returs the field flag of the robot\n
typeof(get_coords(::AbstactRobot)) -> ::Boll
"""
function get_number(robot::AbstractRobot)
    if :number in fieldnames(typeof(robot))
        return number.flag
    else
        return error("This robot has not field number")
    end
end

"""
applies the function `move!` to the field `robot`
"""
move!(robot::AbstractRobot, side::HorizonSide) = HorizonSideRobots.move!(get_robot(robot), side)

"""
applies the function `isborder` to the field `robot`
"""
isborder(robot::AbstractRobot,  side::HorizonSide) = HorizonSideRobots.isborder(get_robot(robot), side)

"""
applies the function `putmarker!` to the field `robot`

"""
putmarker!(robot::AbstractRobot) = HorizonSideRobots.putmarker!(get_robot(robot))

"""
applies the function `ismarker` to the field `robot`

"""
ismarker(robot::AbstractRobot) = HorizonSideRobots.ismarker(get_robot(robot))

"""
applies the function `temperature` to the field `robot`

"""
temperature(robot::AbstractRobot) = HorizonSideRobots.temperature(get_robot(robot))

#------------------------------------------------------------#

"""
robot with coordinates
"""
mutable struct CoordsRobot <: AbstractRobot
    robot::Robot
    coords::Coords
    CoordsRobot(robot) = new(robot, Coords())
end

"""
moves the robot and coordinates to a `side` direction
"""
function move!(robot::CoordsRobot, side::HorizonSide)
    move!(get_robot(robot), side)
    move!(get_coords(robot), side)
end

#------------------------------------------------------------#

"""

"""
mutable struct ChessRobot <: AbstractRobot
    robot::Robot
    flag::Bool
end

function move!(robot::ChessRobot, side::HorizonSide) 
    move!(get_robot(robot), side)
    robot.flag = !get_flag(robot)
end

function putmarker!(robot::ChessRobot)
    if get_flag(robot)
        putmarker!(get_robot(robot))
    end
end



#------------------------------------------------------------#

"""

"""
abstract type AbstractCoordsRobot <: AbstractRobot end

function move!(robot::AbstractCoordsRobot, side::HorizonSide)
    move!(get_robot(robot), side)
    move!(get_coords(robot), side)
end

#------------------------------------------------------------#

"""

"""
mutable struct NChessRobot <: AbstractCoordsRobot
    robot::Robot
    coords::Coords
    number::Integer
end

function putmarker!(robot::NChessRobot)
    x, y = get_xy(get_coords(robot))
    x = x % (2*robot.number)
    y = y  % (2*robot.number)
    if abs(x) in (0:robot.number-1) && abs(y) in (0:robot.number-1) || abs(x) in (robot.number:2*robot.number-1) && abs(y) in (robot.number:2*robot.number-1) 
        putmarker!(get_robot(robot))
    end
end

#------------------------------------------------------------#

"""

"""
mutable struct CrossRobot <: AbstractCoordsRobot
    robot::Robot
    coords::Coords
    flag::Bool
    dx::Integer
    dy::Integer
    function CrossRobot(robot, coords::Coords, flag::Bool, dX::Integer, dY::Integer)
        if dX == 0
            dx = 0
        else
            dx = div(dX, gcd(dX, dY))
        end
        if dY == 0
            dy = 0
        else
            dy = div(dY, gcd(dX, dY))
        end
        return new(robot, coords, flag, dx, dy)
    end
end


function move!(robot::CrossRobot, side::HorizonSide)
    robot.flag = false
    move!(get_robot(robot), side)
    move!(get_coords(robot), side)
    x, y = get_xy(get_coords(robot))
    if robot.dx == 0 || robot.dy == 0
        if x == 0 || y == 0
            robot.flag = true
        end
    elseif y//1 == robot.dx//robot.dy * x || x//1 == -(robot.dx//robot.dy) * y
        robot.flag = true
    end
end

function putmarker!(robot::CrossRobot)
    if get_flag(robot)
        putmarker!(get_robot(robot))
    end
end

#------------------------------------------------------------#
"""
Functions
"""
#------------------------------------------------------------#



"""
moves the robot in a `side` direction to the partition
"""
function moves!(r, side::HorizonSide)::Nothing
    while !isborder(r, side)
        move!(r, side)
    end
end


"""
moves the robot in a `side` direction `number` of times
"""
function moves!(r, side::HorizonSide, number::Integer)
    counter = 0
    for _ in 1:number
        if !isborder(r, side)
            move!(r, side)
            counter += 1
        else
            return number - counter
        end
    end
    return 0
end


"""
moves the robot to `side_to_move` direction along partition in a `side_of_partition` direction
"""
function movesAlong!(r, side_to_move::HorizonSide, side_of_partition::HorizonSide)::Nothing
    while isborder(r, side_of_partition)
        move!(r, side_to_move)
    end
end


"""
moves the robot in a `side` direction to the partition and checks if there is a partition in the `side_for_check` direction\n
returns `true` if there is a partition in the `side_for_check`, else `false`
"""
function movesAndCheck!(r, side::HorizonSide, side_for_check::HorizonSide)::Bool
    while !isborder(r, side)
        if isborder(r, side_for_check)
            return true
        end
        move!(r, side)
    end
    return false
end


"""
moves the robot in a `side` direction `number` of times and checks if there is a partition in the `side_for_check` direction\n
returns `true` if there is a partition in the `side_for_check`, else `false`
"""
function movesAndCheck!(r, side::HorizonSide, side_for_check::HorizonSide, number::Integer)::Bool
    for _ in 1:number
        if isborder(r, side_for_check)
            return true
        end
        move!(r, side)
    end
    return false
end


"""
moves the robot in a `side` direction to the partition and counting steps
"""
function movesAndCounting!(r, side::HorizonSide)::Integer
    count = 0
    while !isborder(r, side)
        move!(r, side)
        count+=1
    end
    return count
end


"""
moves the robot and put markers in a `side` direction to the partition
"""
function marksLine!(r, side::HorizonSide)::Nothing
    putmarker!(r)
    while tryToMove!(r, side)
        putmarker!(r)
    end
end


"""
moves the robot and put markers in a `side` direction `number` of times include start point\n
returns the number of successful steps
"""
function marksLine!(r, side::HorizonSide, number::Integer)::Integer
    putmarker!(r)
    for i in 1:(number-1)
        tryToMove!(r, side)
        putmarker!(r)
    end
    return number
end


"""
moves the robot if possible in a `side` direction one of times
"""
function oneStep!(r, side::HorizonSide)::Nothing
    if !isborder(r, side)
        move!(r, side)
    end
end


"""
moves the robot to a `direction_by_y`-`direction_by_x` angle\n
default directions `(Ost, Sud)`\n
returns stack of directions
"""
function moveAndReturnDirections!(r, direction_by_x::HorizonSide = Ost, direction_by_y::HorizonSide = Sud)::Vector{HorizonSide}
    arr_of_direction::Vector{HorizonSide} = []

    while !all(isborder(r, side) for side in (direction_by_x, direction_by_y))

        while !isborder(r, direction_by_x)
            move!(r, direction_by_x)
            push!(arr_of_direction, direction_by_x)
        end

        while !isborder(r, direction_by_y)
            move!(r, direction_by_y)
            push!(arr_of_direction, direction_by_y)
        end
    end
    return arr_of_direction
end


"""
moves the robot to a `direction_by_y`-`direction_by_x` angle\n
default directions `(Ost, Sud)`\n
"""
function moveToStartplace!(r, direction_by_x::HorizonSide = Ost, direction_by_y::HorizonSide = Sud)::Nothing
    while !all(isborder(r, side) for side in (direction_by_x, direction_by_y))
        moves!(r, direction_by_x)
        moves!(r, direction_by_y)
    end
end


"""
changes direction to the opposite
"""
function reversSide(side::HorizonSide)::HorizonSide
    return HorizonSide((Int(deepcopy(side))+2)%4)
end


"""
moves the robot to the start of the program
"""
function moveToBeginplace!(r, stack_of_direction::Vector{HorizonSide})::Nothing
    while length(stack_of_direction) > 0
        move!(r, reversSide(pop!(stack_of_direction)))
    end
end


"""
creating an array of sides shifted by `shift` clockwise
returns `Vector{HorizonSide}``
"""
function sidesWithShift(shift::Integer = 0)::Vector{HorizonSide}
    sides = [_ for _ in instances(HorizonSide)]
    for i in 1:shift
        for j in 1:(length(sides))
            temp = sides[1]
            sides[1] = sides[j]
            sides[j] = temp
        end
    end
    return sides
end


"""
puts markers in the entire area up to the partition from the `side`\n
`side_begin` - starting direction\n
`side_end` - the direction where the partition that restricts movement is located\n
`size_of_area` - size of n*n area
"""
function marksArea!(r, side_begin::HorizonSide = West, side_end::HorizonSide = Nord)::Nothing
    checker = false

    while !checker
        for side in (side_begin, reversSide(side_begin)) 
            putmarker!(r)
            moveAndPut!(r, side)
            if isborder(r, side_end)
                checker = true
                break
            end
            move!(r, side_end)
        end
    end
end


function marksArea!(r, size_of_area::Integer, side_begin::HorizonSide = West, side_end::HorizonSide = Nord)::Nothing
    size = size_of_area
    count = size
    for n in 1:size
        count = moveAndPut!(r, side_begin, count)
        side_begin = reversSide(side_begin)
        if !isborder(r, side_end)
            move!(r, side_end)
        else
            break
        end
    end
end


"""
moves the work on the markers in a `side` direction
"""
function moveWhileMarker!(r, side::HorizonSide)::Nothing
    while ismarker(r)
        if isborder(r, side)
            break
        end
        move!(r, side)
    end 
end


"""
searches for an object inside the field, stops near the found face and returns the direction to the partition
"""
function searchObject!(r, side_begin::HorizonSide = West, side_end::HorizonSide = Nord)::HorizonSide
    checker = false
    counter = movesAndCounting!(r, side_end)
    moves!(r, reversSide(side_end))
    c = 0

    while !checker
        for side in instances(HorizonSide)
            for _ in 1:counter
                if isborder(r, nextSideConterclockwise(side))
                    checker = true
                    break
                end
                if isborder(r, side)
                    checker = true
                    side = nextSideClockwise(side)
                    break
                end
                move!(r, side)
            end

            if checker
                return side
            end
            c += 1
            if c == 2
                counter-=1
                c = 0
            end
        end
    end
end


"""
returns the following direction is counterclockwise
"""
function nextSideConterclockwise(side::HorizonSide)::HorizonSide
    return HorizonSide((Int(deepcopy(side))+1)%4)
end


"""
returns the following direction is clockwise
"""
function nextSideClockwise(side::HorizonSide)::HorizonSide
    return HorizonSide((Int(deepcopy(side))+3)%4)
end


"""
returns the coordinates of the robot relative to the start of a program\n
`sides` - array with directions
"""
function countingCoordinate(sides::Vector{HorizonSide})::Tuple{Integer, Integer}
    arr = deepcopy(sides)
    x = 0
    y = 0

    while length(arr)>0
        a = pop!(arr)
        if a == Sud
            y+=1
        elseif a == Nord
            y-=1
        elseif a == Ost
            x+=1
        else
            x-=1
        end
    end
    return (x, y)
end


"""
trying to move to `side_to_try` direction 
"""
function tryMove!(r, side_to_try::HorizonSide = Ost)
    side_to_move = nextSideClockwise(side_to_try)
    checker_side = deepcopy(side_to_move)
    partition = true
    counter = 0

    if isborder(r, side_to_move) && isborder(r, side_to_try)
        side_to_move = reversSide(side_to_move)
    end

    while partition
        if isborder(r, side_to_try)
            partition = true
            tryMove!(r, side_to_move)
            counter += 1
        else
            partition = false
            move!(r, side_to_try)
            for _ in 1:counter
                tryMove!(r, reversSide(side_to_move))
            end
        end  
    end

end


"""
trying to move to `side_to_try` direction\n
bypasses the the partitions conterclockwise\n
retuns `true` and move to `side_to_try` if can that\n
else returns `false` and stay initial position
"""
function tryToMoveConterclockwise!(r, side_to_try::HorizonSide)::Bool
    side_to_move = nextSideClockwise(side_to_try)
    counter = 0
    partition = true

    if !isborder(r, side_to_try)
        move!(r, side_to_try)
        return true
    end
    
    while partition

        if isborder(r, side_to_move) && isborder(r, side_to_try)
            moves!(r, reversSide(side_to_move), counter)
            return false
        end
        if isborder(r, side_to_try)
            partition = true
            move!(r, side_to_move)
            counter += 1
        else
            partition = false
            move!(r, side_to_try)
            movesAlong!(r, side_to_try, reversSide(side_to_move))
            moves!(r, reversSide(side_to_move), counter)
            return true
        end
    end
end


"""
trying to move to `side_to_try` direction\n
bypasses the the partitions clockwise\n
retuns `true` and move to `side_to_try` if can that\n
else returns `false` and stay initial position
"""
function tryToMoveClockwise!(r, side_to_try::HorizonSide)::Bool
    side_to_move = nextSideConterclockwise(side_to_try)
    counter = 0
    partition = true

    if !isborder(r, side_to_try)
        move!(r, side_to_try)
        return true
    end

    while partition

        if isborder(r, side_to_move) && isborder(r, side_to_try)
            moves!(r, reversSide(side_to_move), counter)
            return false
        end
        if isborder(r, side_to_try)
            partition = true
            move!(r, side_to_move)
            counter += 1
        else
            partition = false
            move!(r, side_to_try)
            movesAlong!(r, side_to_try, reversSide(side_to_move))
            moves!(r, reversSide(side_to_move), counter)
            return true
        end
    end
end


"""
trying to trying to move to `side_to_try` direction\n
if the partition cannot be bypassed returns false
"""
function tryToMove!(r, side_to_try::HorizonSide)
    checker = false
    if tryToMoveClockwise!(r, side_to_try)
        checker = true
    elseif tryToMoveConterclockwise!(r, side_to_try)
        checker = true
    end
    return checker
end


"""
marks the field in the specified order depending on the type of `robot`
"""
function marks!(r, sides::NTuple{2, HorizonSide} = (Nord, West))::Nothing
    side_to_move = sides[1]
    side_to_marks = sides[2]

    marksLine!(r, side_to_marks)
    while !isborder(r, side_to_move)
        tryToMove!(r, side_to_move)
        side_to_marks = reversSide(side_to_marks)
        marksLine!(r, side_to_marks)
    end
end


"""

"""
function tryToMoveModify!(r, side_to_try::HorizonSide)::Bool
    side_to_move = nextSideConterclockwise(side_to_try)
    steps = 1

    while isborder(r, side_to_try)
        side_to_move = reversSide(side_to_move)
        if moves!(r, side_to_move, steps) != 0
            moves!(r, reversSide(side_to_move), div(steps, 2))
            return false
        end
        steps += 1
    end

    move!(r, side_to_try)

    while isborder(r, reversSide(side_to_move))
        move!(r, side_to_try)
    end

    moves!(r, reversSide(side_to_move), div(steps, 2))
    return true
end


"""

"""
function movements!(r, side::HorizonSide)
    while tryToMoveModify!(r, side) end
end

"""

"""
function movements!(r, side::HorizonSide, number::Integer)
    for _ in 1:number 
        tryToMoveModify!(r, side)
    end
end


"""

"""
function spiralBypass!(condition::Function, r::AbstractCoordsRobot)
    counter = 1
    side = HorizonSide(0)
    while !condition(r)
        moves!(r, side, counter)
        if Int(side) == 1 || Int(side) == 3
            counter+=1
        end
        side = nextSideConterclockwise(side)
    end
end


"""

"""
function counterPartition!(r::Robot, side_to_move::HorizonSide = Ost)
    counter = 0
    while !isborder(r, nextSideConterclockwise(side_to_move))
        while tryToMove!(r, side_to_move)
            if isborder(r, nextSideConterclockwise(side_to_move))
                movesAlong!(r, side_to_move, nextSideConterclockwise(side_to_move))
                counter+=1
            end
        end
        while tryToMove!(r, reversSide(side_to_move)) end
        move!(r, nextSideConterclockwise(side_to_move))
    end
    return counter
end
