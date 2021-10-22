include("..\\libs\\FunctionsRobot.jl")

function chessMarkers!(r::Robot, number_of_steps::Integer)
    for side in (West, Ost)
        while !isborder(r, side)
            if number_of_steps%2 == 0
                putmarker!(r)
                moves!(r, side, 2)
            else
                oneStep!(r, side)
                putmarker!(r)
                oneStep!(r, side)
            end
        end
        if isborder(r, Nord)
            break
        else
            oneStep!(r, Nord)
        end
    end
end

function chess_desk!(r)
    sides = moveAndReturnDirections!(r)
    while !(isborder(r, Nord) && (isborder(r, West)||isborder(r,Ost)))
        chessMarkers!(r, length(sides))
    end
    moveToStartplace!(r)
    moveToBeginplace!(r, sides)
end