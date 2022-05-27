using Polynomials
using Plots
include("sem_7.jl")

"""Вычисляет значение многочлена и производной многочлена p в точке x"""
function polyval(P, x)
    dQ = 0
    Q = P[1]
    for i in 2:length(P)
        dQ = dQ*x + Q
        Q = Q*x + P[i]
    end
    return Q, dQ
end

"""Замыкает MyP. Вычисляет -MyP(x)/MyP'(x)"""
function rP(x)
    y, dy = polyval(MyP, x)
    return -y/dy
end

"""Метод Ньютоня для вычисления приближенного значения функции"""
function newton(r::Function, x; epsilon = 1e-8, max_num_iter = 20)
    num_iter = 0
    r_x = r(x)
    while num_iter < max_num_iter && abs(r_x) > epsilon
        x += r_x
        r_x = r(x)
        num_iter += 1
    end

    if abs(r_x) <= epsilon
        return x
    else
        return NaN
    end
end

#=
cosX_equals_X = newton(x -> (cos(x)-x) / (sin(x)+1), 0.5)    # уравнение cos(x)=x, решенное с пом-ью метода Ньютона
println(cosX_equals_X)
=#

"""Вычисляет приближенное значение производной"""
function appr_d(f, x, h=1e-8)
    return (f(x + h) - f(x)) / h
end

"""Ищет приближенный корень уравнения f(x)=0"""
function newton_wthout_der(f::Function, x; h=1e-8, epsilon = 1e-8, max_num_iter = 20)
    num_iter = 0
    r_x = -f(x) / appr_d(f, x, h)
    while num_iter < max_num_iter && abs(r_x) > epsilon
        x += r_x
        r_x = -f(x) / appr_d(f, x, h)
        num_iter += 1
    end

    if abs(r_x) <= epsilon
        return x
    else
        return NaN
    end
end

#MyP = Polynom{Int64}([-1, 0, 0, 1])    # многочлен z^3 - 1
""""""
function draw()
    function rP(x)
        y, dy = polyval(MyP, x)
        return -y/dy
    end
    MyP = Polinom{Int64}([-1, 0, 0, 1])
    X = []
    Y = []

    M = rand(Float64, (100, 2))
    for i in 1:100
        a::Vector{ComplexF64} = [newton(rP, M[i]+M[100+i]*im), newton(rP, -M[i]+M[100+i]*im),
                newton(rP, M[i]-M[100+i]*im), newton(rP, -M[i]-M[100+i]*im)]
        
        for k in a
            push!(X, k.re)
            push!(Y, k.im)
        end
    end
    
    plot(X, Y, seriestype = :scatter, title = "Roots")
end
    