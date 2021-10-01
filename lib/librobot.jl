"""
Library of custom function for HorizonSideRoots by Droideka501
"""

"""
moves the robot in the "side" direction to the partition
"""
function moves!(r::Robot, side::HorizonSide)::Nothing
    while !isborder(r, side)
        move!(r, side)
    end
end


"""
moves the robot in the "side" direction "number" of times
"""
function moves!(r::Robot, side::HorizonSide, number::Integer)::Nothing
    for _ in 1:number
        move!(r, side)
    end
end


"""
moves the robot to the "direction_by_y"-"direction_by_x" angle\n
default directions (Ost, Sud)\n
returns stack of directions
"""
function moveAndReturnDirections!(r::Robot, direction_by_x::HorizonSide = Ost, direction_by_y::HorizonSide = Sud)::Vector{HorizonSide}
    arr_of_direction::Vector{HorizonSide} = []

    while !(isborder(r, direction_by_x) && isborder(r, direction_by_y))

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
moves the robot to the "direction_by_y"-"direction_by_x" angle\n
default directions (Ost, Sud)\n
"""
function moveToStartplace!(r::Robot, direction_by_x::HorizonSide = Ost, direction_by_y::HorizonSide = Sud)::Nothing
    while !(isborder(r, direction_by_x) && isborder(r, direction_by_y))
        moves!(r, direction_by_x)
        moves!(r, direction_by_x)
    end
end


"""
changes direction to the opposite
"""
function reversSide(side::HorizonSide)::HorizonSide
    return HorizonSide(Int((Int(side)+2)%4))
end


"""
moves the robot to the start of the program
"""
function moveToBeginplace!(r::Robot, stack_of_direction::Vector{HorizonSide})::Nothing
    while length(stack_of_direction) > 0
        move!(r, reversSide(pop!(stack_of_direction)))
    end
end
