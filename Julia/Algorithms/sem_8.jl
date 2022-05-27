using Plots

"""Считает сумму первых n чисел вида 1/k! для k=1:n"""
function eyler(n::Integer)
    s = 0.0
    a = 1.0
    
    for k in 1:n+1 
        s += a
        a /= k
    end
    
    return s
end


"""Считает сумму первых n чисел вида 1/k! для k=1,2,3,... До те пор, пока она не перестанет изменяться (что обязательно когда-то произойдет)"""
function eyler()
    s = 0
    a = 1
    k = 0
    #цикл остановиться по причине неточности компьютерного вычисления (есть округление после запятой, что приводит к наращиванию погрешности, в итоге числа 1/n и 1/(n+1) будут равны)
    while s + a != s
        k += 1
        s += a
        a /= k
    end

    return s
end

"""Вычисляет значение значение sin(x) для заданного x с заданной максимально допустимой погрешностью"""
function sin(x, eps=1e-8)
    xx=x^2
    a=x
    m=2
    s=typeof(x)(0) 
    
    while abs(a) > eps
        s += a
        a = -a*xx / m / (m+1)
        m += 2
    end
    
    return s
end

"""Вычисляет значение значение sin(x) для заданного x"""
function sin(x, eps=1e-8)
    xx=x^2
    a=x
    m=2
    s=typeof(x)(0) 
    
    while s + a != s
        s += a
        a = -a*xx / m / (m+1)
        m += 2
    end
    
    return s
end

"""Вычисляет exp(x) с помощью ряда Тейлора"""
function exp_(x)
    s = 0
    a = 1
    k = 0
    
    while s + a != s
        k += 1
        s += a
        a /= k
        a *= x
    end

    return s
end

"""Вычисляет cos(x) с помощью ряда Тейлора"""
function cos_(x)
    xx=x^2
    a = 1
    m = 1
    s = 0 
    
    while s + a != s
        s += a
        a = -a*xx / m / (m+1)
        m += 2
    end
    
    return s
end


"""Возвращает значение n-ой частичной суммы ряда для cos(x) в точке х"""
function part_sum(n, x)
    xx = x^2
    a = 1
    m = 1
    s = 0 
    
    while (m-1)/2 < n
        s += a
        a = -a*xx / m / (m+1)
        m += 2
    end
    
    return s
end

"""Вычисляет функцию Бесселя 1-го рода порядка m в точке x ∈ R с машинной точностью"""
function besselj(M::Integer, x::Real)
    sqrx = x*x
    a = 1/factorial(M)
    m = 1
    s = 0 
    
    while s + a != s
        s += a
        a = -a * sqrx /(m*(M+m)*4)
        m += 1
    end
    
    return s*(x/2)^M
end


function draw()
    #=
    x = 1:0.1:10
    p = plot()
    for n in 2:2:16
        plot!(p, x, part_sum.(n, x))
    end
    display(p)
    =#
    x1 = 0:0.1:20
    p1 = plot()
    for m in 1:5
        plot!(p1, x1, besselj.(m, x1))
    end
    display(p1)
end
