include("..\\libs\\FunctionsRobot.jl")

condition = r -> ismarker(r)

function searchMarkerWithPartition!(r)
    spiralBypass!(condition, r)
end
    