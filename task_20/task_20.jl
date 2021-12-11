include("..\\libs\\FunctionsRobot.jl")


function countPartition!(r)
    back_path = BackPath(r, (Sud, West))
    print(counterPartition!(r))
    BackPath(r, (Sud, West))
    back!(r, back_path)
end
    