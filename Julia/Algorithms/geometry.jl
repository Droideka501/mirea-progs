
using LinearAlgebra

#-----------------------------------------

Vector2D{T<:Real} = NamedTuple{(:x, :y), Tuple{T,T}}

Base. +(a::Vector2D{T},b::Vector2D{T}) where T = Vector2D{T}(Tuple(a) .+ Tuple(b))

Base. -(a::Vector2D{T}, b::Vector2D{T}) where T = Vector2D{T}(Tuple(a) .- Tuple(b))

Base. *(α::T, a::Vector2D{T}) where T = Vector2D{T}(α .* Tuple(a))

LinearAlgebra.norm(a::Vector2D) = norm(Tuple(a))
# norm(a) - длина вектора, эта функция опредедена в LinearAlgebra

LinearAlgebra.dot(a::Vector2D{T}, b::Vector2D{T}) where T = dot(Tuple(a), Tuple(b))
# dot(a,b)=|a||b|cos(a,b) - скалярное произведение, эта функция определена в LinearAlgebra

Base.cos(a::Vector2D{T}, b::Vector2D{T}) where T = dot(a,b)/norm(a)/norm(b)

xdot(a::Vector2D{T}, b::Vector2D{T}) where T = a.x*b.y - a.y*b.x
# xdot(a,b)=|a||b|sin(a,b) - косое произведение

Base.sin(a::Vector2D{T}, b::Vector2D{T}) where T = xdot(a,b)/norm(a)/norm(b)

Base.angle(a::Vector2D{T}, b::Vector2D{T}) where T = atan(sin(a,b),cos(a,b))
Base.sign(a::Vector2D{T}, b::Vector2D{T}) where T = sign(sin(a,b))

#--================================================================================
Segment2D{T<:Real} = NamedTuple{(:A, :B), NTuple{2,Vector2D{T}}}

#---------------------------------------------------------
function intersect(s1::Segment2D{T},s2::Segment2D{T}) where T
    A = [s1.B[2]-s1.A[2]  s1.A[1]-s1.B[1]
         s2.B[2]-s2.A[2]  s2.A[1]-s2.B[1]]

    b = [s1.A[2]*(s1.A[1]-s1.B[1]) + s1.A[1]*(s1.B[2]-s1.A[2])
         s2.A[2]*(s2.A[1]-s2.B[1]) + s2.A[1]*(s2.B[2]-s2.A[2])]

    x,y = A\b
    # !!!! Если матрица A - вырожденная, то произойдет ошибка времени выполнения

    if isinner((;x, y), s1)==false || isinner((;x, y), s2)==false
        return nothing
    end

    return (;x, y) #Vector2D{T}((x,y))
end

isinner(P::Vector2D, s::Segment2D) = 
    (s.A.x <= P.x <= s.B.x || s.A.x >= P.x >= s.B.x)  && 
    (s.A.y <= P.y <= s.B.y || s.A.y >= P.y >= s.B.y)

#=--==================================================================
abstract type AbstractPolygon{T<:Real} end

struct Polygon{T} <: AbstracPolygon{T} 
    vertices::Vector{Vector2D{T}}
end
get_vertices(polygon::Polygon) = polygon.vertices
num_vertices(polygon::Polygon) = polygon.vertices[begin] != polygon.vertices[end] ? length(polygon.vertices) : length(polygon.vertices)-1  

struct ConvexPolygon{T} <: AbstractPolygon{T}
    vertices::Vector{Vector2D{T}}
end
get_vertices(polygon::ConvexPolygon) = polygon.vertices

#-----------------------------------------------------------------------------------

function isinner(A::Vector2D{T}, polygon::AbstractPolygon{T})::Bool where T
# проверка принадлежности точки внутренности многоугольника (не обязательно выпуклого)
    flag = double_ended!(polygon)
    sum_angles = 0.0
    for i in firstindex(polygon.vertices):lastindex(polygon.vertices)-1
        sum_angles += angle(polygon[i+1]-A, polygon[i]-A)
    end

    if flag == true
        single_ended!(polygon)
    end

    if sum_angles < pi # фактически равно 0
        return true # точка внутри многоугольника
    else
        return false # точка снаружи
    end
end

function isinner(A::Vector2D{T}, polygon::ConvexPolygon{T})::Bool where T
# проверка принадлежности точки внутренности ВЫПУКЛОГО многоугольника

    flag = double_ended!(polygon)
    sign_prev = sign(polygon[begin+1]-A, polygon[begin]-A)
    for i in firstindex(polygon.vertices)+1:lastindex(polygon.vertices)-1
        sign_cur += sign(polygon[i+1]-A, polygon[i]-A)
        if sign_prev * sign_cur < 0
            return false
        end 
    end

    if flag == true
        single_ended!(polygon)
    end

    return true
end

function isconvex(plygon::AbstractPolygon)::Bool
# проверка, является ли заданный многоугольник выпуклым
end

function double_ended!(polygon::AbstractPolygon)::Bool # дублирует в конце вектора его первый элемент, если изначально этого дублирования не было
    if polygon[begin] != polygon[end]
        push!(polygon, polygon[begin])
        return true # входной вектор изменён
    end
    return false # входной вектор не изменён 
end

function single_ended!(polygon::AbstractPolygon)::Bool # удаляет из конца вектора элемент, дублирующий первый, если такой лемент был
    if polygon[begin] == polygon[end]
        pop!(polygon)
        return true # входной вектор изменён
    end
    return false # входной вектор не изменён 
end

#------------------------------------------------------------------

function jarvis(points::Vector{Vector2D{T}})::ConvexPolygon{T} where T<:Real # алгоритм Джарвиса построения выпуклой оболочки заданного множества точек плоскости
    @assert length(points) > 1 # иначе операция в строке 9 будет не возможна
    # yyy = [points[i][2] for i in 1:length(points)] # - так создавался бы дополонительный массив
    yyy = (points[i][2] for i in 1:length(points))  # - а так массив не создается, вместо массива используется генератор
    i_start = findmin(yyy) # индекс самой нижней точки
    convex_shell = [i_start]
    ort_base = Vector2D{Int}((1,0)) # - этот вектор задает начальное базовое направление (горизонтално вправо)
    while next!(convex_shell, points, ort_base) != i_start
        ort_base = convex_shell[end] - convex_shell[end-1]  # - не нулевой вектор, задающий очередное базовое направление
    end
    return convex_shell # В конце и в начале массива convex_shell дважды содержится значение i_start 
end


function next!(convex_shell::Vector{Int64}, points::Vector{Vector2D{T}}, ort_base::Vector2D{T}) where T<:Real
    cos_max = typemin(T)
    i_base = convex_shell[end]
    resize!(convex_shell, length(convex_shell)+1)
    for i in eachindex(points)
        if points[i] == points[i_base] # тут не обязательно, что i == i_base
            continue
        end
        ort_i = points[i] - points[i_base] # - не нулевой вектор, задающий направление на очередную точку
        cos_i = cos(ort_base, ort_i)
        if cos_i > cos_max
            cos_max = cos_i
            convex_shell[end] = i 
        elseif cos_i == cos_max && quad_len(ort_i) > quad_len(ort_base) # на луче, содержащем сторону выпуклого многоугольника, может оказаться более двух точек заданного множества (надо выбрать самую дальнюю из них)
            convex_shell[end] = i
        end
    end
    return convex_shell[end]
end

quad_len(vec) = dot(vec, vec)

#-------------------------------------

function grekhom(points::Vector{Vector2D{T}})::ConvexPolygon{T} where T<:Real # алгоритм Грехома построения выпуклой оболочки заданного множества точек плоскости
    
end
=#