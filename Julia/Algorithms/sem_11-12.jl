import Base
import LinearAlgebra
import Plots

"""Двумерный вектор (псевдоним)"""
Vector2D{T<:Real} = NamedTuple{(:x, :y),Tuple{T,T}}

"""Двумерный сегмент"""
Segment2D{T<:Real} = NamedTuple{(:A, :B),NTuple{2,Vector2D{T}}}

+(A::Vector2D{T}, B::Vector2D{T}) where {T} = Vector2D{T}(Tuple(A) .+ Tuple(B))
-(A::Vector2D{T}, B::Vector2D{T}) where {T} = Vector2D{T}(Tuple(A) .- Tuple(B))
*(coeff::T, A::Vector2D{T}) where {T} = Vector2D{T}(coeff .* Tuple(A))
LinearAlgebra.norm(a::Vector2D) = LinearAlgebra.norm(Tuple(a))
LinearAlgebra.dot(a::Vector2D{T}, b::Vector2D{T}) where {T} = LinearAlgebra.dot(Tuple(a), Tuple(b))
Base.cos(a::Vector2D{T}, b::Vector2D{T}) where {T} = LinearAlgebra.dot(a, b) / LinearAlgebra.norm(a) / LinearAlgebra.norm(b)
xdot(a::Vector2D{T}, b::Vector2D{T}) where {T} = a.x * b.y - a.y * b.x
Base.sin(a::Vector2D{T}, b::Vector2D{T}) where {T} = xdot(a, b) / LinearAlgebra.norm(a) / LinearAlgebra.norm(b)
Base.angle(a::Vector2D{T}, b::Vector2D{T}) where {T} = atan(sin(a, b), cos(a, b))
Base.sign(a::Vector2D{T}, b::Vector2D{T}) where {T} = sign(xdot(a, b))


abstract type AbstractPolygon{T<:Real} end

"""Структоура полигона (многоугольника)"""
struct Polygon{T} <: AbstractPolygon{T}
    vertices::Vector{Vector2D{T}}
    Polygon{T}(vertices) where {T} = new(double_ended!(vertices))
end

"""Дублирует в конце вектора его первый элемент, если изначально этого дублирования не было"""
function double_ended!(vertices::Vector{Vector2D})
    if vertices[begin] != vertices[end]
        push!(vertices, polygon[begin])
    end
    return vertices
end

get_vertices(polygon::Polygon) = polygon.vertices
num_vertices(polygon::Polygon) = polygon.vertices[begin] != polygon.vertices[end] ? length(polygon.vertices) : length(polygon.vertices) - 1


struct ConvexPolygon{T} <: AbstractPolygon{T}
    vertices::Vector{Vector2D{T}}
    ConvexPolygon{T}(vertices) where {T} = new(double_ended!(vertices))
end
get_vertices(polygon::ConvexPolygon) = polygon.vertices

Plots.plot!(polygon::AbstractPolygon; kwargs...) = plot!(current(), polygon.vertices; kwargs...)
Plots.plot!(p::Plots.Plot, polygon::AbstractPolygon; kwargs...) = plot!(p, polygon.vertices; kwargs...)
Plots.plot(polygon::AbstractPolygon; kwargs...) = plot(polygon.vertices; kwargs...)


"""Точка пересечения двух отрезуов"""
function intersect(f::Segment2D{T}, s::Segment2D{T}) where {T}
    if (f.B.y - f.A.y != 0)
        q = (f.B.x - f.A.x) / (f.A.y - f.D.y)
        sn = (s.A.x - s.B.x) + (s.A.y - s.B.y) * q
        if sn == 0
            return nothing
        end
        fn = (s.A.x - f.A.x) + (s.A.y - f.A.y) * q
        n = fn / sn
    else
        if s.A.y - s.B.y == 0
            return nothing
        end
        n = (s.A.y - f.A.y) / (s.A.y - s.B.y)
    end
    result = Vector2D{T}((s.A.x + (s.B.x - s.A.x) * n, s.A.y + (s.B.y - s.A.y) * n))
    return result
end

"""Угол между линиями, заданными уравнениями k1 * x + b1 и k2 * x + b2"""
function angle_between(k1, b1, k2, b2)
    x1 = 1
    y1 = k1 * x1
    x2 = 1
    y2 = k2 * x2
    return acos((x1 * x2 + y1 * y2) / sqrt((x1 * x1 + y1 * y1) * (x2 * x2 + y2 * y2)))
end

"""Угол между сегментами"""
function angle_between(f::Segment2D{T}, s::Segment2D{T}) where {T}
    x1 = f.A.x - f.B.x
    y1 = f.A.y - f.B.y
    x2 = s.A.x - s.B.y
    y2 = s.A.y - s.B.y
    return acos((x1 * x2 + y1 * y2) / sqrt((x1 * x1 + y1 * y1) * (x2 * x2 + y2 * y2))) - pi / 2
end

"""Проверка, лежат ли две точки по одну сторону от линии"""
function on_one_side(A::Vector2D, B::Vector2D, f) 
    return f(A.x, A.y) * f(B.x, B.y) > 0
end

"""Проверка, лежат ли две точки по одну сторону от прямой"""
function on_one_side_line(A::Vector2D, B::Vector2D, k, b)
    return (A.y > k * A.x + b) == (B.y > k * B.x + b)
end

"""Проверк, лежит ли точка внутри выпуклого многоугольника"""
function is_convex(points)
    first_edge = Segment2D{Int}(points[1], points[2])
    sharp = 0
    obt = 0
    for i in 3:length(points)
        second_edge = Segment2D{Int}(points[i-1], points[i])
        if angle_between(first_edge, second_edge) > π / 2
            obt += 1
        else
            sharp += 1
        end
        first_edge = second_edge
    end
    return obt == sharp
end

"""Проверк, лежит ли точка внутри многоугольника"""
function is_inner(A::Vector2D{T}, polygon::AbstractPolygon{T})::Bool where {T}
    sum_angles = 0.0
    for i in firstindex(polygon.vertices):lastindex(polygon.vertices)-1
        sum_angles += angle(polygon[i+1] - A, polygon[i] - A)
    end
    return sum_angles < pi
end

"""Выпуклая оболочка по Джарвису"""
function jarvis_alg(points::Vector{Vector2D{T}})::ConvexPolygon{T} where {T<:Real}

    function next!(convex_shell::Vector{Int64}, points::Vector{Vector2D{T}}, ort_base::Vector2D{T}) where {T<:Real}
        cos_max = typemin(T)
        i_base = convex_shell[end]
        resize!(convex_shell, length(convex_shell) + 1)
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

    @assert length(points) > 1
    ydata = [points[i][2] for i in 1:length(points)]
    i_start = findmin(ydata)
    convex_shell = [i_start[1]]
    ort_base = Vector2D{Int}((1, 0))
    while next!(convex_shell, points, ort_base) != i_start
        ort_base = convex_shell[end] - convex_shell[end-1]
    end
    return ConvexPolygon{T}(points[convex_shell])
end

"""Выпуклая оболочка по Грекхому"""
function grekhom!(points::Vector{Vector2D{T}})::ConvexPolygon{T} where {T<:Real}
    ydata = (points[i][2] for i in 1:length(points))
    i_start = findmin(ydata)
    points[begin], points[i_start] = points[i_start], points[begin]
    sort!(@view(points[begin+1:end]), by=(point -> angle(point, Vector2D{T}(1, 0))))
    push!(points, points[begin])
    convex_polygon = [firstindex(points), firstindex(points) + 1, firstindex(points) + 2]
    for i in firstindex(points)+3:lastindex(points)
        while sign(points[i] - points[convex_polygon[end]], points[convex_polygon[end-1]] - points[convex_polygon[end]]) < 0
            pop!(convex_polygon)
        end
        push!(convex_polygon, i)
    end
    pop!(points)
    return ConvexPolygon{T}(points[convex_polygon])
end

"""Функция, возвращающая значение ориентированной площади заданного плоского многоугольника методом трапеций"""
function orinet_sq_trap(poly::Polygon{T}) where {T<:Real}
    res = 0.0
    for i in firstindex(poly.vertices):lastindex(poly.vertices)-1
        res += (poly.vertices[i].y + poly.vertices[i+1].y) * (poly.vertices[i+1].x - poly.vertices[i].x) / 2
    end
    return res
end

"""Функция, возвращающая значение ориентированной площади заданного плоского многоугольника методом треугольников"""
function orient_sq_triangle(poly::Polygon{T}) where {T<:Real}
    res = 0.0
    for i in firstindex(poly.vertices)+1:lastindex(poly.vertices)-1
        res += xdot(poly.vertices[i] - poly.vertices[0], poly.vertices[i+1] - poly.vertices[0])
    end
    return res
end

"""Добавление точки в выпуклую оболочку"""
function add_point(conv::ConvexPolygon{T}, p::Vector2D{T}) where {T<:Real}
    if (length(conv.vertices) < 3)
        push!(conv.vertices(p))
        return conv
    end
    if !is_inner(p, conv)
        min_angle = -10
        max_angle = 10
        max_ind = 1
        min_ind = 1
        for i in 1:length(conv.vertices)
            if angle(conv.vertices[i], p) >= max_angle
                max_angle = angle(conv.vertices[i], p)
                max_ind = i
            elseif angle(conv.vertices[i], p) <= max_angle
                min_angle = angle(conv.vertices[i], p)
                min_ind = i
            end
        end
        i = 0
        res = ConvexPolygon{T}()
        while i < min(min_ind, max_ind)
            push!(res.vertices, conv.vertices[i])
        end
        push!(res.vertices, p)
        i = max(min_ind, max_ind)
        while i < length(conv.vertices)
            push!(res.vertices, conv.vertices[i])
        end
        conv = res
        return res
    end
    return nothing
end

"""Построение выпуклой оболочки"""
function built_conv(points::Vector{Vector2D{T}}) where {T<:Real}
    return reduce(add_point, points)
end

"""Построение выпуклой оболочки и ее площадь"""
function build_conv_with_square(points::Vector{Vector2D{T}}) where {T<:Real}
    square = 0.0
    conv = ConvexPolygon{T}()
    for point in points
        if !isnothing(add_point(conv, point))
            square += (conv.vertices[end].y + point) * (point - conv.vertices[end].x) / 2
        end
    end
    return conv, square
end

"""Явлется ли заданная последовательность точек, вершинами некоторого многоугольника"""
function is_poly(points::Vector{Vector2D{T}}) where {T}
    for i in 1:length(points)-1
        f = Segment2D{T}(points[i], points[i+1])
        for j in 1:i-1
            s = Segment2D{T}(points[j], points[j+1])
            if !isnothing(intersect(f, s))
                return false
            end
        end
    end
    return true
end


"""Объединение множеств точек, вычисление выпуклой оболочки"""
function unite(f::ConvexPolygon{T}, s::ConvexPolygon{T}) where {T}
    res = f
    for new_point in s.vertices
        add_point(res, new_point)
    end
    return res
end
