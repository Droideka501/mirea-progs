
"""Приведение матрицы к ступенчатому виду с помощью элементарных преобразований строк"""
function transformToSteps!(Matrix)
    coef(a, b) = b / a
    
    n, m = size(Matrix)
    for t in 1:m-1
        for i in t+1:n
            c = coef(Matrix[t, t], Matrix[i, t])
            Matrix[i, t] = 0
            for j in t+1:m
                Matrix[i, j] -= c * Matrix[t, j] #преобразовываем строки
            end
        end
    end

    return Matrix
end

 """Приведение матрицы к ступенчатому виду с помощью элементарных переобразований столбцов"""
function transformToStepsCol!(Matrix)
    coef(a, b) = b / a
    
    n, m = size(Matrix)
    for t in m:-1:1
        for i in t-1:-1:1
            c = coef(Matrix[t, t], Matrix[t, i])
            
            Matrix[t, i] = 0
            for j in t-1:-1:1
                Matrix[j, i] -= c * Matrix[j, t] #преобразовываем столбцы
            end

        end
    end

    return Matrix
end

"""Приведение матрицы к ступенчатому виду, возвращает вектор индесов столбцов с нулями"""
function transformToStepsMod(M)
    Matrix = deepcopy(M)
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

    v = []
    for i in 1:n
        if Matrix[i, i] == 0
            push!(v, i)
        end
    end
    return Matrix, v
end

"""Ранк матрицы"""
function rank_(M)
    Matrix = deepcopy(M)
    Matrix, v = transformToStepsMod(Matrix)
    return size(Matrix, 1)-size(v, 1)
end

"""Вычисление определителя"""
function det_(M)
    Matrix = deepcopy(M)
    Matrix, v = transformToStepsMod(Matrix)
    if !isempty(v)
        return 0
    end
    det = 1
    for i in 1:size(Matrix, 1)
        if Matrix[i, i] == 0
            break
        end
        det *= Matrix[i, i]
    end
    return det
end

"""Решение СЛАУ"""
function solutionSLAE(A, b)
    M = deepcopy(A)
    B = deepcopy(b)
    D = hcat(M, B)
    transformToSteps!(D)
    return D
end


"""Обратная матрица"""
function inverse(M)
    return inv(M)
end

