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

#newton(x -> (cos(x)-x)/(sin(x)+1), 0.5)+

"""Возвращающей значение многочлена и его производной в заданной точке"""
function polyval(P,x)
    dQ = 0
    Q = P[1]
    for i in 2:length(P)
        dQ = dQ*x + Q
        Q = Q*x + P[i]
    end
    return Q, dQ
end

"""Замыкание внешней переменной P"""
function r(P, x) # what is it?
    y, dy = polyval(P, x)
    return -y/dy
end


struct Polynomial{T}
    coeff::Vector{T}

    function Polynomial{T}(coeff) where T
        n = 0
        for c in reverse(coeff)
            if c == 0
                n+=1
            end
        end
        new(coeff[1:end-n])
    end
end

deg(p::Polynomial{T}) where{T} = length(p.coeff) - 1

function eyler(n)
    # n - заданное число
    s = 0.0
    a = 1.0
    for k in 1:n+1
    # границы значений индекса k по отношению к прежнему варианту теперь смещены на 1 вправо
        s += a
        a /= k
    end
end

function eyler()
    s = 0
    a = 1
    k = 0
    while s + a != s
        k += 1
        s += a
        a /= k
    end
    return s
end # Объяснение состоит в том, что
 # при вычислении s+a должны будут складываться
 # соответствующие 53-х битные мантиссы (здесь речь идет
 #  о формате типа Float64). Но сначала порядок меньшего
 #   слагаемого должен быть приведен к порядку большего
 #   слагаемого путем "сдвига" его мантиссы вправо с заменой
 #    "освобождающихся" битов нулями. Таким образом, если сдвиг
 #     составит 53 бита или больше, то мантисса меньшего числа
 #      окажется полностью замененной нулями.

 function eyler_sin(x)
     a = x
     s = 0
     e = 0.000000001
     k = 1
     while abs(a) > e
         s += a
         k += 1
         a *= -x*x/(2*k-1)/(2*k-2)
     end
     s
 end

function Base.sin(x,e)
    xx=x^2
    a=x
    m=2
    s=typeof(x)(0)
    while abs(a)>e
        s+=a
        a=-a*xx/m/(m+1)
        m+=2
    end
    #УТВ: |sin(x)-s|<= ε
    return s
end

# the best sin function
function sin_(x)
    xx=x^2
    a=x
    m=2
    s=typeof(x)(0)
    while s+a != s
        s+=a
        a=-a*xx/m/(m+1)
        m+=2
    end
    #УТВ: |sin(x)-s| <= 1е-16
    return s
end

function exp_(x, eps)
    sum = 1;
    f = x
    k = 2
    while f > eps
        sum += f
        f *= x/k
        k += 1
    end
    sum
end

function harmonic_sum()
    s=0.0
    k=1
    a=1.0
    while s+a != s
        a=1/k
        s+=a
        k+=1
    end
    return s
end

function eyler_cos(x, n)
    mx2 = -x*x
    part = 1
    sum = 1
    for i = 2:2:n
        part *= mx2/((i-1)*i)
        sum += part
    end
    sum
end

function cos_(x, e = 0.0000000000001)
    s = 0
    an = 1
    n = 0
    while abs(an) > e
        s += an
        n += 1
        an *= -x*x/(2*n-1)/(2*n)
    end
    s
end

using Plots

x = 0:0.1:10
p = plot()
plot!(x, eyler_cos.(x, 2))
plot!(x, eyler_cos.(x, 4))
plot!(x, eyler_cos.(x, 8))
plot!(x, eyler_cos.(x, 16))
display(p)

using SpecialFun

function bessel(nu::Real, x::AbstractFloat)
    if isinteger(nu)
        if typemin(Cint) <= nu <= typemax(Cint)
            return bessel(Cint(nu), x)
        end
    elseif x < 0
        throw(DomainError())
    end
    real(bessel(float(nu), complex(x)))
end