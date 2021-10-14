"""
Library of custom function for HorizonSideRoots by Droideka501 \n
link to repository https://github.com/Droideka501/mirea-progs
"""

"""
moves the robot in a `side` direction to the partition
"""
function moves!(r::Robot, side::HorizonSide)::Nothing
    while !isborder(r, side)
        move!(r, side)
    end
end


"""
moves the robot in a `side` direction `number` of times
"""
function moves!(r::Robot, side::HorizonSide, number::Integer)::Nothing
    for _ in 1:number
        if !isborder(r, side)
            move!(r, side)
        else 
            break
        end
    end
end


"""
moves the robot in a `side` direction to the partition and checks if there is a partition in the `side_for_check` direction
"""
function movesAndCheck!(r::Robot, side::HorizonSide, side_for_check::HorizonSide)::Bool
    while !isborder(r, side)
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
function movesAndCounting!(r::Robot, side::HorizonSide)::Integer
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
function marksLine!(r::Robot, side::HorizonSide)::Nothing
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
function marksLine!(r::Robot, side::HorizonSide, number::Integer)::Integer
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
function oneStep!(r::Robot, side::HorizonSide)::Nothing
    if !isborder(r, side)
        move!(r, side)
    end
end


"""
moves the robot to a `direction_by_y`-`direction_by_x` angle\n
default directions `(Ost, Sud)`\n
returns stack of directions
"""
function moveAndReturnDirections!(r::Robot, direction_by_x::HorizonSide = Ost, direction_by_y::HorizonSide = Sud)::Vector{HorizonSide}
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
function moveToStartplace!(r::Robot, direction_by_x::HorizonSide = Ost, direction_by_y::HorizonSide = Sud)::Nothing
    while !all(isborder(r, side) for side in (direction_by_x, direction_by_y))
        moves!(r, direction_by_x)
        moves!(r, direction_by_y)
    end
end


"""
changes direction to the opposite
"""
function reversSide(side::HorizonSide)::HorizonSide
    return HorizonSide((Int(side)+2)%4)
end


"""
moves the robot to the start of the program
"""
function moveToBeginplace!(r::Robot, stack_of_direction::Vector{HorizonSide})::Nothing
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
function marksArea!(r::Robot, side_begin::HorizonSide = West, side_end::HorizonSide = Nord)::Nothing
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


function marksArea!(r::Robot, size_of_area::Integer, side_begin::HorizonSide = West, side_end::HorizonSide = Nord)::Nothing
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
function moveWhileMarker!(r::Robot, side::HorizonSide)::Nothing
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
function searchObject!(r::Robot, side_begin::HorizonSide = West, side_end::HorizonSide = Nord)::HorizonSide
    checker = false
    while !checker
        for side in (side_begin, reversSide(side_begin)) 
            checker = movesAndCheck!(r, side)
            if checker
                return side
            end
            move!(r, side_end)
        end
    end
end


"""
returns the following direction is counterclockwise
"""
function nextSideConterclockwise(side::HorizonSide)::HorizonSide
    return HorizonSide((Int(side)+1)%4)
end


"""
returns the following direction is clockwise
"""
function nextSideClockwise(side::HorizonSide)::HorizonSide
    return HorizonSide((Int(side)+3)%4)
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