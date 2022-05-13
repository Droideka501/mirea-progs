# Практика 5+

1. Расширенный алгоритм Евклида+
2. Обращение обратимых элементов кольца вычетов+
3. Приближенное решение уравнений методом деления отрезка пополам+

```julia
function bisec(f::Function, a, b; atool = 1e-15)
    @assert f(a)*f(b) < 0
    # Инвариант: f(a)*f(b) < 0
    while b-a > atool
        x = (a+b)/2
        f_a = f(a)
        if f_a == 0
            return x
        elseif f_a * f(x) > 0
            a = x
        else
            b = x
        end
    end
    return x
end
```

4. Реализовать встроенную функцию isprime(n), O(log(n))

```julia
function isprime_(n::T)::Bool where T <: Integer
    for i in 2:round(T, sqrt(n))
        if n % i == 0
            return false
        end
    end
    return true
end
```

5. Реализовать алгоритм "решето Эратосфена", вычисляющий все простые числа, не превосходящие заданного натурального числа

```julia
function eratosphen(n::Integer)::BitVector
    is_prime = ones(Bool, n) 
    is_prime[1] = false # 1 — не является простым числом
    for i in 2:round(Int, sqrt(n))
        if is_prime[i] 
            for j in (i*i):i:n 
                is_prime[j] = false
            end
        end
    end
    return (1:n)[is_prime] # filter(x -> is_prime[x], 1:n) 
end
```

6. Простые делители числа и их кратности