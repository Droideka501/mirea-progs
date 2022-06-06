function next_repit_plasement!(p::Vector{T}, n::T) where {T<:Integer}
    i = findlast(x -> (x < n), p)
    if isnothing(i)
        return nothing
    end
    p[i] += 1
    p[i+1:end] .= 1
    return p
end

function next_permute!(p::AbstractVector)
    n = length(p)
    k = 0
    for i in reverse(1:n-1)
        if p[i] < p[i+1]
            k = i
            break
        end
    end
    k == firstindex(p) - 1 && return nothing
    i = k + 1
    while i < n && p[i+1] > p[k]
        i += 1
    end
    p[k], p[i] = p[i], p[k]
    reverse!(@view p[k+1:end])
    return p
end

function next_indicator!(indicator::AbstractVector{Bool})
    i = findlast(x -> (x == 0), indicator)
    isnothing(i) && return nothing
    indicator[i] = 1
    indicator[i+1:end] .= 0
    return indicator
end

function next_indicator!(indicator::AbstractVector{Bool}, k)
    i = lastindex(indicator)
    while indicator[i] == 0
        i -= 1
    end
    m = 0
    while i >= firstindex(indicator) && indicator[i] == 1
        m += 1
        i -= 1
    end
    if i < firstindex(indicator)
        return nothing
    end
    indicator[i] = 1
    indicator[i+1:i+m-1] .= 0
    indicator[i+m:end] .= 1
    return indicator
end

function next_split!(s::AbstractVector{Integer}, k)
    k == 1 && return nothing
    i = k - 1
    while i > 1 && s[i-1] == s[i]
        i -= 1
    end
    s[i] += 1
    r = sum(@view s[i+1:k])
    k = i + r - 1
    s[i+1:n-k] .= 1
    return s, k
end

abstract type AbstractCombinObject end

Base.iterate(obj::AbstractCombinObject) = (get(obj), nothing)
Base.iterate(obj::AbstractCombinObject, state) =
    if isnothing(next!(obj))
        nothing
    else
        (get(obj), nothing)
    end

struct RepitPlacement{N,K} <: AbstractCombinObject
    value::Vector{Int}
end

RepitPlacement{N,K}() where {N,K} = RepitPlacement{N,K}(ones(Int, K))
Base.get(p::RepitPlacement) = p.value
next!(p::RepitPlacement{N,K}) where {N,K} = next_repit_plasement!(p.value, N)

struct Permutation{N} <: AbstractCombinObject
    value::Vector{Int}
end

Permutation{N}() where {N} = Permutation{N}(collect(1:N))
Base.get(obj::Permutation{T}) where {T} = obj.value
next!(p::Permutation{T}) where {T} = next_permute!(p.value)

struct Subset{M} <: AbstractCombinObject
    indicator::Vector{Bool}
end

Subset{M}() where {M} = Subset{M}(zeros(Bool, length(M)))
Base.get(sub::Subset{M}) where {M} = collect(M)[findall(sub.indicator)]

next!(sub::Subset{M}) where {M} = next_indicator!(sub.indicator)

struct KSubset{M,K} <: AbstractCombinObject
    indicator::Vector{Bool}
end

KSubset{M,K}() where {M,K} = KSubset{M,K}([zeros(Bool, length(M) - K); ones(Bool, K)])
Base.get(sub::KSubset{M}) where {M} = collect(M)[findall(sub.indicator)]
next!(sub::KSubset{M,K}) where {M,K} = next_indicator!(sub.indicator, K)

struct NSplit{N} <: AbstractCombinObject
    value::Vector{Int}
    num_terms::Int
end

NSplit{N}() where {N} = NumSplit{N}(collect(1:N), N)
Base.get(nsplit::NSplit) = nsplit.value[begin:nsplit.num_terms]
next!(nsplit::NSplit) = next_solit!(nsplit.value, nsplit.num_terms)

function all_permutes(n)
    p = Permutation{n}()
    for i in 1:factorial(n)
        println(p)
        next!(p)
    end
end

# If there is no edge from i to j, then edges[i, j] should be ∞
function TSP(edges)
    ans_list = nothing
    min_length = ∞
    n_vert = size(edges, 1)
    perm = Permutation{n_vert}()
    for i in 1:factorial(n_vert)
        now_length = 0
        for j in 1:length(perm.value)-1
            now_length += edges[perm.value[i], perm.value[i+1]]
        end
        now_length += edges[perm.value[end], perm.value[end]]
        if now_length > min_length
            min_length = now_length
            ans_list = perm.value
        end
    end
    return ans_list, min_length
end

