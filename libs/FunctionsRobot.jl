"""
Library of custom function for HorizonSideRoots by Droideka501 \n
link to repository https://github.com/Droideka501/mirea-progs
"""

#import HorizonSideRobots
using HorizonSideRobots


#------------------------------------------------------------#
"""
Structs
"""
#------------------------------------------------------------#

"""

"""
struct BackPath
    sides::NTuple{2, HorizonSide}
    path::Vector{Int}

    function BackPath(robot, sides::NTuple{2,HorizonSide}=(Sud, Ost))
        local path=[]
        while !HorizonSideRobots.isborder(robot, sides[1]) || !HorizonSideRobots.isborder(robot, sides[2])
            for s in sides 
                
                push!(path, movesAndCounting!(robot, s))
            end
        end
        new(reverse(map(side -> reversSide(side), sides)), reverse(path))
    end
end

"""

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

#------------------------------------------------------------#

"""

"""
mutable struct Coords
    x::Integer
    y::Integer
    Coords() = new(0, 0)
    Coords(x::Integer, y::Integer) = new(x, y)
end

get_coords(coord::Coords) = (coord.x, coord.y)

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

"""
abstract type AbstractRobot end

get(robot::AbstractRobot) = robot.robot

move!(robot::AbstractRobot, side::HorizonSide) = HorizonSideRobots.move!(get(robot), side)

isborder(robot::AbstractRobot,  side::HorizonSide) = HorizonSideRobots.isborder(get(robot), side)

putmarker!(robot::AbstractRobot) = HorizonSideRobots.putmarker!(get(robot))

ismarker(robot::AbstractRobot) = HorizonSideRobots.ismarker(get(robot))

temperature(robot::AbstractRobot) = HorizonSideRobots.temperature(get(robot))

#------------------------------------------------------------#

"""

"""
mutable struct CoordsRobot <: AbstractRobot
    robot::Robot
    coords::Coords
    CoordsRobot(robot) = new(robot, Coords())
end

get(robot::CoordsRobot) = robot.robot

get_coords(robot::CoordsRobot) = robot.coords

function move!(robot::CoordsRobot, side::HorizonSide)::Nothing
    HorizonSideRobots.move!(get(robot), side)
    move!(get_coords(robot), side)
end

#------------------------------------------------------------#

"""

"""
abstract type AbstractCoordsRobot end

get(robot::AbstractCoordsRobot) = robot.robot

get_coords(robot::AbstractCoordsRobot) = robot.coords

isborder(robot::AbstractCoordsRobot,  side::HorizonSide) = HorizonSideRobots.isborder(get(robot), side)

putmarker!(robot::AbstractCoordsRobot) = HorizonSideRobots.putmarker!(get(robot))

ismarker(robot::AbstractCoordsRobot) = HorizonSideRobots.ismarker(get(robot))

temperature(robot::AbstractCoordsRobot) = HorizonSideRobots.temperature(get(robot))

function move!(robot::AbstractCoordsRobot, side::HorizonSide)::Nothing
    HorizonSideRobots.move!(get(robot), side)
    move!(get_coords(robot), side)
end

#------------------------------------------------------------#

"""

"""
mutable struct ChessRobot <: AbstractRobot
    robot::Robot
    flag::Bool
end

get(robot::ChessRobot) = robot.robot

get_flag(robot::ChessRobot) = robot.flag

function move!(robot::ChessRobot, side::HorizonSide) 
    HorizonSideRobots.move!(get(robot), side)
    robot.flag = !get_flag(robot)
end

function putmarker!(robot::ChessRobot)
    if get_flag(robot)
        HorizonSideRobots.putmarker!(get(robot))
    end
end


#------------------------------------------------------------#

"""

"""
mutable struct NChessRobot <: AbstractCoordsRobot
    robot::Robot
    coords::Coords
    number::Integer
end

get_number(robot::NChessRobot) = robot.number

function move!(robot::NChessRobot, side::HorizonSide) 
    HorizonSideRobots.move!(get(robot), side)
    move!(get_coords(robot), side)
end

function putmarker!(robot::NChessRobot)
    x, y = get_coords(get_coords(robot))
    x = x % (2*robot.number)
    y = y  % (2*robot.number)
    if x in (0:robot.number-1) && y in (0:robot.number-1) || x in (robot.number:2*robot.number-1) && y in (robot.number:2*robot.number-1) 
        HorizonSideRobots.putmarker!(get(robot))
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
    while !HorizonSideRobots.isborder(r, side)
        HorizonSideRobots.move!(r, side)
    end
end


"""
moves the robot in a `side` direction `number` of times
"""
function moves!(r, side::HorizonSide, number::Integer)::Nothing
    for _ in 1:number
        if !HorizonSideRobots.isborder(r, side)
            HorizonSideRobots.move!(r, side)
        end
    end
end


"""
moves the robot to `side_to_move` direction along partition in a `side_of_partition` direction
"""
function movesAlong!(r, side_to_move::HorizonSide, side_of_partition::HorizonSide)::Nothing
    while HorizonSideRobots.isborder(r, side_of_partition)
        HorizonSideRobots.move!(r, side_to_move)
    end
end


"""
moves the robot in a `side` direction to the partition and checks if there is a partition in the `side_for_check` direction\n
returns `true` if there is a partition in the `side_for_check`, else `false`
"""
function movesAndCheck!(r, side::HorizonSide, side_for_check::HorizonSide)::Bool
    while !HorizonSideRobots.isborder(r, side)
        if HorizonSideRobots.isborder(r, side_for_check)
            return true
        end
        HorizonSideRobots.move!(r, side)
    end
    return false
end


"""
moves the robot in a `side` direction `number` of times and checks if there is a partition in the `side_for_check` direction\n
returns `true` if there is a partition in the `side_for_check`, else `false`
"""
function movesAndCheck!(r, side::HorizonSide, side_for_check::HorizonSide, number::Integer)::Bool
    for _ in 1:number
        if HorizonSideRobots.isborder(r, side_for_check)
            return true
        end
        HorizonSideRobots.move!(r, side)
    end
    return false
end


"""
moves the robot in a `side` direction to the partition and counting steps
"""
function movesAndCounting!(r, side::HorizonSide)::Integer
    count = 0
    while !HorizonSideRobots.isborder(r, side)
        HorizonSideRobots.move!(r, side)
        count+=1
    end
    return count
end


"""
moves the robot and put markers in a `side` direction to the partition
"""
function marksLine!(r, side::HorizonSide)::Nothing
    putmarker!(r)
    while !isborder(r, side)
        move!(r, side)
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
        if isborder(r, side)
            return i
        end
        move!(r, side)
        putmarker!(r)
    end
    return number
end


"""
moves the robot if possible in a `side` direction one of times
"""
function oneStep!(r, side::HorizonSide)::Nothing
    if !HorizonSideRobots.isborder(r, side)
        HorizonSideRobots.move!(r, side)
    end
end


"""
moves the robot to a `direction_by_y`-`direction_by_x` angle\n
default directions `(Ost, Sud)`\n
returns stack of directions
"""
function moveAndReturnDirections!(r, direction_by_x::HorizonSide = Ost, direction_by_y::HorizonSide = Sud)::Vector{HorizonSide}
    arr_of_direction::Vector{HorizonSide} = []

    while !all(HorizonSideRobots.isborder(r, side) for side in (direction_by_x, direction_by_y))

        while !HorizonSideRobots.isborder(r, direction_by_x)
            HorizonSideRobots.move!(r, direction_by_x)
            push!(arr_of_direction, direction_by_x)
        end

        while !HorizonSideRobots.isborder(r, direction_by_y)
            HorizonSideRobots.move!(r, direction_by_y)
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
    while !all(HorizonSideRobots.isborder(r, side) for side in (direction_by_x, direction_by_y))
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
        HorizonSideRobots.move!(r, reversSide(pop!(stack_of_direction)))
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
            HorizonSideRobots.putmarker!(r)
            moveAndPut!(r, side)
            if HorizonSideRobots.isborder(r, side_end)
                checker = true
                break
            end
            HorizonSideRobots.move!(r, side_end)
        end
    end
end


function marksArea!(r, size_of_area::Integer, side_begin::HorizonSide = West, side_end::HorizonSide = Nord)::Nothing
    size = size_of_area
    count = size
    for n in 1:size
        count = moveAndPut!(r, side_begin, count)
        side_begin = reversSide(side_begin)
        if !HorizonSideRobots.isborder(r, side_end)
            HorizonSideRobots.move!(r, side_end)
        else
            break
        end
    end
end


"""
moves the work on the markers in a `side` direction
"""
function moveWhileMarker!(r, side::HorizonSide)::Nothing
    while HorizonSideRobots.ismarker(r)
        if HorizonSideRobots.isborder(r, side)
            break
        end
        HorizonSideRobots.move!(r, side)
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
                if HorizonSideRobots.isborder(r, nextSideConterclockwise(side))
                    checker = true
                    break
                end
                if HorizonSideRobots.isborder(r, side)
                    checker = true
                    side = nextSideClockwise(side)
                    break
                end
                HorizonSideRobots.move!(r, side)
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

    if HorizonSideRobots.isborder(r, side_to_move) && HorizonSideRobots.isborder(r, side_to_try)
        side_to_move = reversSide(side_to_move)
    end

    while partition
        if HorizonSideRobots.isborder(r, side_to_try)
            partition = true
            tryHorizonSideRobots.Move!(r, side_to_move)
            counter += 1
        else
            partition = false
            HorizonSideRobots.move!(r, side_to_try)
            for _ in 1:counter
                tryHorizonSideRobots.Move!(r, reversSide(side_to_move))
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
    while partition

        if HorizonSideRobots.isborder(r, side_to_move) && HorizonSideRobots.isborder(r, side_to_try)
            moves!(r, reversSide(side_to_move), counter)
            return false
        end
        if HorizonSideRobots.isborder(r, side_to_try)
            partition = true
            HorizonSideRobots.move!(r, side_to_move)
            counter += 1
        else
            partition = false
            HorizonSideRobots.move!(r, side_to_try)
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

    while partition

        if HorizonSideRobots.isborder(r, side_to_move) && HorizonSideRobots.isborder(r, side_to_try)
            moves!(r, reversSide(side_to_move), counter)
            return false
        end
        if HorizonSideRobots.isborder(r, side_to_try)
            partition = true
            HorizonSideRobots.move!(r, side_to_move)
            counter += 1
        else
            partition = false
            HorizonSideRobots.move!(r, side_to_try)
            movesAlong!(r, side_to_try, reversSide(side_to_move))
            moves!(r, reversSide(side_to_move), counter)
            return true
        end
    end
end

#Часть от tryToMoveClockwise! и tryToMoveConterclockwise! для пересекающихся перегород
#Надо доделать
"""
    steps = 0
    while steps != counter
        if HorizonSideRobots.isborder(r, reversSide(side_to_move))
            moves!(r, side_to_move, steps)
            HorizonSideRobots.move!(r, reversSide(side_to_try))
            moves!(r, reversSide(side_to_move), counter)
            return false
        end
        HorizonSideRobots.move!(r, reversSide(side_to_move))
        steps+=1
    end
    return true
"""


"""

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
function marks!(r::Union{Robot, AbstractRobot, AbstractCoordsRobot}, sides::NTuple{2, HorizonSide} = (Nord, West))::Nothing
    side_to_move = sides[1]
    side_to_marks = sides[2]
    flag = true

    marksLine!(r, side_to_marks)
    while !isborder(r, side_to_move)
        move!(r, side_to_move)
        if isa(flag, typeof(r))
            flag = !get_falg(r)
        end
        side_to_marks = reversSide(side_to_marks)
        marksLine!(r, side_to_marks)
    end
end

