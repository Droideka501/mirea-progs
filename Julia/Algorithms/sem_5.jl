using Revise

struct Polynom
    coeffs::Vector{Int} # coefficients of polynom p(x) = c1 + c2*x + c3*x^2...

    Polynom(arr::Vector{Int}) = new(arr)

    function +(p1::Polynom, p2::Polynom)
        p = p1.coeffs > p2.coeffs ? p1 : p2
        for i in 1:min(length(p1.coeffs), length(p2.coeffs))
            p.coeffs[i] += p1.coeffs > p2.coeffs ? p1.coeffs[i] : p2.coeffs[i]
        end
    end

    function print(p::Polynom)
        io = IOBuffer()
        for i in p.coeffs
            count = 0
            Base.print(io, i, " x^", count)
            count += 1
        end
        return String(take!(io))
    end

end