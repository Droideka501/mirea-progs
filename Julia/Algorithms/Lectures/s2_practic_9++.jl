#---------------------------------------------------------------

function add_1(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A) == size(B)
    C = similar(A)
    for i in 1:size(A,1), j in 1:size(A,2) # 
        C[i,j] = A[i,j] + B[i,j]
    end
    #= это эквивалентно:
    for i in 1:size(A,1)
        for j in 1:size(A,2)
            C[i,j] = A[i,j] + B[i,j]
        end
    end
    =#
    return C
end

function add_2(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A) == size(B)
    C = similar(A)
    for  j in 1:size(A,2), i in 1:size(A,1) # - это более педпочтиельный вариант (преимущество проявляется на больших матрицах)
        C[i,j] = A[i,j] + B[i,j]
    end
    return C
end
 
using LinearAlgebra

function mul(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number 
    @assert size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    At=A'
    for j in 1:size(C,2), i in 1:size(C,1)
        p=0.0
        for k in 1:size(A,2) # size(A,2) == size(B, 1)
            p += At[k,i]*B[k,j]
        end
        C[i,j] = p
    end
    return C
end

function mul_1(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number 
    @assert size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    for i in 1:size(C,1), j in 1:size(C,2)
        @views C[i,j] = dot(A[i,:],B[:,j])
    end
    #= это эквивалентно:
    for i in 1:size(C,1), j in 1:size(C,2)
        C[i,j] = T(0)
        for k in 1:size(A,2) # size(A,2) == size(B, 1)
            C[i,j] += A[i,k]*conj(B[k,j])
        end
    end
    =#
    return C
end

function mul_2(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    for j in 1:size(C,2), i in 1:size(C,1)
        @views C[i,j] = dot(A[i,:], B[:,j])
    end
    return C
end

function mul_3(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    @assert size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    At = A'
    for j in 1:size(C,2), i in 1:size(C,1)
        @views C[i,j] = dot(At[:,i], B[:,j])
    end
    return C
end


#----------------------------------------------------
print("N = ")
N = parse(Int, readline())
#=
При N=10_000 выигрыш примерно на порядок
при N=1000 он всего раза в два
=#
A = randn(N,N)
B = randn(N,N)
println("Варианты реализации сложения матриц:")
@time add_1(A,B);
@time add_2(A,B);
println("Варианты реализации перемножения матриц:")
@time mul(A,B);
#=
@time mul_1(A,B);
@time mul_2(A,B);
@time mul_3(A,B);
=#
println()