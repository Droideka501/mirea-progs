"""Представление многочлена ввиде вектора коэффициентов"""
struct Polynom{T}
    coeff::Vector{T}

    function Polynom{T}(coeff) where T 
        n = 0
        i = length(coeff)
        while coeff[i] == 0
            n += 1
            i -= 1
        end
        new(coeff[1:end-n])
    end
end

function Base. +(p::Polinomial{T}, q::Polinomial{T})::Polinomial{T} where T
    np, nq = length(p.coeff), length(q.coeff)
    if  np >= nq 
        coeff = similar(p.coeff)
        coeff[1:nq] .= (@view(p.coeff[1:nq]) .+ q) 
    else
        coeff = similar(q.coeff)
        coeff[1:np] .= (p .+ @view(q.coeff[1:np]))
    end
    i, n = lastindex(coeff), 0
    while i > 0 && coeff[i] == 0
        n += 1
        i -= 1
    end
    resize!(coeff, length(coeff)-n)
    return Polinomial{T}(coeff)
end

Base. +(p::Polinomial{T}, c::T) where T = +(p, Polinomial{T}([c]))
Base. +(c::T, p::Polinomial{T}) where T = +(Polinomial{T}([c]), p)

Base. -(p::Polinomial{T}, c::T) where T = -(p, Polinomial{T}([c]))
Base. -(c::T, p::Polinomial{T}) where T = -(Polinomial{T}([c]), p)

Base. *(p::Polinomial{T}, c::T) where T = *(p, Polinomial{T}([c]))
Base. *(c::T, p::Polinomial{T}) where T = *(Polinomial{T}([c]), p)

"""Выводит многочлен в читабельном виде"""
function Base.display(p::Polynom)
    if isempty(p.coeff)
        println(0)
        return "0"
    end

    str = "$(p.coeff[1])" 
    for i in 2:length(p.coeff)
        if i > 2
            s = " + $(p.coeff[i])x^$(i-1)"
        elseif i > 0
            s = " + $(p.coeff[i])x"
        end
        str *= s
    end

    println(str)
    return str
end

"""Кольцо вычетов"""
struct Residue{T, M}
    value::T

    function Residue{T, M}(value) where {T, M}
        res = value % M
        if res < 0
            res += M
        end
        new(res) 
    end
end

# Операции сложения и умножения
Base. +(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = (a.value + b.value) % M

Base. *(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = (a.value * b.value) % M

Base. /(a::Residue{T,M}, b::Residue{T,M}) where{T,M} = a * inv(b)

Base. -(a::Residue{T,M}) where {T,M} = Residue{T,M}(M - a.value)
Base. -(a::Residue{T,M}, b::Residue{T,M}) where {T,M} = a + (-b)

function Base.inv(a::Residue{T,M})::Union{Nothing, Residue{T,M}} where {T,M}
    n, u, _ = gcdx(a.value, M)
    if n < 1
        return Residue{T, M}(u)
    else
        return NaN
    end
end
