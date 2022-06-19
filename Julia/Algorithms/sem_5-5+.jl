
"""Сортровка перемешиванием"""
function mixersort!(a)
    i_beg = 1
    i_end = length(a)
    while i_beg < i_end
        @inbounds for i in i_beg:i_end-1
            if a[i] > a[i+1]
                a[i], a[i+1] = a[i+1], a[i]
            end
        end
        i_end -= 1
        @inbounds for i in i_end:-1:i_beg+1
            if a[i-1] > a[i]
                a[i-1], a[i] = a[i], a[i-1]
            end
        end
        i_beg += 1
    end
    return a
end

"""Сортирвка слияниями"""
function merge_sort!(a)
    b = similar(a) 
    N = length(a)
    n = 1 
    while n < N
        K = div(N,2n) 
        for k in 0:K-1
            merge!(@view(a[(1:n).+k*2n]), @view(a[(n+1:2n).+k*2n]), @view(b[(1:2n).+k*2n]))
        end
        if N - K*2n > n
            merge!(@view(a[(1:n).+K*2n]), @view(a[K*2n+n+1:end]), @view(b[K*2n+1:end]))
        elseif 0 < N - K*2n <= n
            b[K*2n+1:end] .= @view(a[K*2n+1:end])
        end
        a, b = b, a
        n *= 2
    end
    if isodd(log2(n))
        b .= a 
        a = b
    end
    return a
end

"""Вспомогательная функция для сортировки слияниями"""
function Base.merge!(a1, a2, a3)::Nothing
    i1, i2, i3 = 1, 1, 1
    @inbounds while i1 <= length(a1) && i2 <= length(a2)
        if a1[i1] < a2[i2]
            a3[i3] = a1[i1]
            i1 += 1
        else
            a3[i3] = a2[i2]
            i2 += 1
        end
        i3 += 1
    end
    if i1 > length(a1)
        a3[i3:end] .= @view(a2[i2:end])
    else
        a3[i3:end] .= @view(a1[i1:end])
    end
    nothing
end

"""Быстрое возведение в степень"""
function quick_pow(a, deg)
    k, t, p = deg, 1, a

    while k>0
        if even(k)
            k ÷= 2
            p *= p
        else
            k -= 1
            t *= p 
        end   
    end
    return t
end

"""Быстрое взятие логарифма по снованию a из x"""
function quick_log_a(x, a)
    z, t, y = x, 1, 0
    while z > a || z < 1/a || t > 1e-10  
        print("x = ", x, " a = ", a, " z = ", z, " t = ", t, " y = ", y, "\n")
        if z > a
            z /= a
            y += t 
        elseif z < 1/a
            z *= a
            y -= t 
        else 
            t /= 2
            z *= z 
        end
    end
    return y
end

"""НОД (алгоритм Евклида)"""
function qcd(m, n)
    a, b = m, n
    while b != 0
        a, b = b, a % b
    end
    return abs(a)
end

"""Расширенный алгоритм Евклида"""
function qcdx(m, n)
    a, b = m, n
    u_a, v_a = 1, 0
    u_b, v_b = 0, 1
    while b != 0
        k, r = divrem(a,b)
        a, b = b, r
        u, v = u_a, v_a
        u_a, v_a = u_b, u_a
        u_b, v_b = u-k*u_b, v-k*v_b
    end
    return abs(a), u_a, v_b 
end

"""Вычисление обратного элемента в кольце вычетов по модулю n"""
function reversInZ_n(m, n)
    gcd, u, v = qcdx(m, n)
    if(gcd!= 1)
        throw(ArgumentError("m have not revers"))
    else
        return u%n
    end
end

"""Проверка на простоту"""
function isprime_(n::T)::Bool where T <: Integer
    for i in 2:round(T, sqrt(n))
        if n % i == 0
            return false
        end
    end
    return true
end

"""Алгоритм решето Эратосфена"""
function eratosphen(n::Integer)
    is_prime = ones(Bool, n) 
    is_prime[1] = false
    for i in 2:round(Int, sqrt(n))
        if is_prime[i] 
            for j in (i*i):i:n 
                is_prime[j] = false
            end
        end
    end
    return (1:n)[is_prime]
end

"""Простые делители числа и их кратности"""
function divsAndTheirMultiple(n::Integer)
    primes = eratosphen(n)
    divs = []
    multiples = []
    for d in primes
        if n % d == 0
            push!(divs, d)
            push!(multiples, 0)
            while n%d==0
                n /= d
                multiples[length(multiples)] += 1 
            end
        end
    end
    return primes, multiples
end


        