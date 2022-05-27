using LinearAlgebra

"""Обратный ход метода Гаусса"""
function reversedGauss(Matrix, b)
    x = similar(b)
    n = size(Matrix, 1)

    for k in 0:n-1
        x[n - k] = (b[n - k] - sum(@view(Matrix[n-k, n-k+1 : n]) .* @view(x[n-k+1:n]))) / Matrix[n-k, n-k]
    end
    return x
end

"""Тестирует обратный ход гаусса"""
function test_gauss(N, f)
    _, U = lu(rand(N, N))
    X = f(U, ones(N))
    return U*X
end

"""Приводит матрицу к ступенчатому виду"""
function toUpperTriangle!(Matrix)
    coef(a, b) = b / a
    
    n, m = size(Matrix)
    for t in 1:m-1
        for i in t+1:n
            c = coef(Matrix[t, t], Matrix[i, t])
            Matrix[i, t] = 0
            for j in t+1:m
                Matrix[i, j] -= c * Matrix[t, j]
            end
        end
    end

    return Matrix
end

"""СЛАУ к ступенчатому виду"""
function SLAUToUpperTriangle!(Matrix, B)
    coef(a, b) = b / a
    n = size(Matrix, 1)

    for t in 1:n-1
        cur_i = argmax(@view(Matrix[t:n, t]))

        for i in t:n # swaps lines
            temp = Matrix[t, i]
            Matrix[t, i] = Matrix[cur_i, i]
            Matrix[cur_i, i] = temp
        end
        temp = B[cur_i]
        B[cur_i] = B[t]
        Matrix[t] = temp

        cur_el = Matrix[t, t]
        if cur_el == 0
            throw(DomainError((t, t), "equals 0"))
        end
        for i in t+1:n
            c = coef(cur_el, Matrix[i, t])
            Matrix[i, t] = 0
            B[i] -= c * B[t]
            for j in t+1:n
                Matrix[i, j] -= c * Matrix[t, j]
            end
        end
    end

    return Matrix
end

"""Определитель матрицы"""
function det(Matrix)
    toUpperTriangle!(Matrix)
    det = 1
    i = 1
    while (i <= size(Matrix, 1))
        if (Matrix[i, i] != 0)
            det *= Matrix[i, i]
            i+=1
        else break end
    end
    return det
end

"""Ранг матрицы"""
function rank(Matrix)
    toUpperTriangle!(Matrix)
    i = 1
    while(Matrix[i, i] != 0)
        i+=1
    end
    return i-1
end

"""Обратная матрица"""
#Не работает, надо переопределить toUpperTriangle!() для не квадратной матрицы
function reversMatix(Matrix)
    E = diagm([1 for i in 1:size(Matrix, 1)])
    D = 
    toUpperTriangle!(Matrix)
    Temp = Matrix[end:-1:begin]
end

function add(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number
    size(A) == size(B)
    C = similar(A)
    for  j in 1:size(A,2), i in 1:size(A,1)
        C[i,j] = A[i,j] + B[i,j]
    end
    return C
end
 
function mul(A::AbstractMatrix{T}, B::AbstractMatrix{T}) where T<:Number 
    size(A,2) == size(B, 1)
    C = Matrix{T}(undef, size(A,1), size(B,2))
    At=A'
    for j in 1:size(C,2), i in 1:size(C,1)
        p=0.0
        for k in 1:size(A,2)
            p += At[k,i]*B[k,j]
        end
        C[i,j] = p
    end
    return C
end
