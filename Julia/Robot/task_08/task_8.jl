include("..\\libs\\FunctionsRobot.jl")

function search_out!(r::Robot)
    side = West
    counter = 1

    while isborder(r, Nord)
        moves!(r, side, counter)
        side = reversSide(side)
        counter += 1
    end
end