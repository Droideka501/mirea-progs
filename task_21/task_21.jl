include("..\\libs\\FunctionsRobot.jl")


function countPartitionModify!(r)
    back_path = BackPath(r, (Sud, West))
    print(counterPartition!(r), "\tHorizontal\n")
    BackPath(r, (Nord, West))
    print(counterPartition!(r, Sud), "\tVertical\n")
    BackPath(r, (Sud, West))
    back!(r, back_path)
end
    