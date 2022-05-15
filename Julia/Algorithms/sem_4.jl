"""Сортировка Хоара"""
function quick_sort!(A)
    length(A) <= 1 && return A
    N = length(A)
    left, right = part_sort!(A, A[rand(1:N)])
    quick_sort!(left)
    quick_sort!(right)
    return A
end

"""Вспомогательная сортировка"""
function part_sort!(A, b)
    N = length(A)
    K, L, M = 0, 0, N
    @inbounds while L < M
        if A[L+1] == b
            L += 1
        elseif A[L+1] > b
            A[L+1], A[M] = A[M], A[L+1]
            M -= 1
        else
            L += 1; K += 1
            A[L], A[K] = A[K], A[L]
        end
    end
    return @view(A[1:K]), @view(A[M+1:N])
end

"""Вычисление k-ой порядковой статистики методом Хоара"""
function order_statistics!(A::AbstractVector{T}, i::Integer)::T where T
    function find(index_range)
        left_range, right_range = part_sort!(A, index_range, A[rand(index_range)])
        if i in left_range
            return find(left_range) 
        elseif i in right_range
            return find(right_range)
        else
            return A[i]
        end
    end
    find(firstindex(A):lastindex(A))
end

@inline function part_sort!(A, index_range::AbstractUnitRange, b)
    K, L, M = index_range[1]-1, index_range[begin]-1, index_range[end]
    @inbounds while L < M 
        if A[L+1] == b
            L += 1
        elseif A[L+1] > b
            A[L+1], A[M] = A[M], A[L+1]
            M -= 1
        else
            L += 1; K += 1
            A[L], A[K] = A[K], A[L]
        end
    end    
    return index_range[begin]:K, M+1:index_range[end]
end

"""Вычисление медианы массива"""
function median(A::AbstractVector{T})
    if length(A)%2==0
        return order_statistics!(A, length(A)/2)
    else
        return (order_statistics!(A, length(A)/2)+order_statistics!(A, length(A)/2+1))/2
    end
end

"""Поиск первых k наименьших элементов массива"""
function minimums(array, k)
    N = length(array)
    k_minimums = sort(array[1:k])
    i = k
    while i < length(array)
        i += 1
        if array[i] < k_minimums[end]
            k_minimums[end] = array[i]
            insert_end!(k_minimums)
        end
    end
    return k_minimums
end            

function insert_end!(array)::Nothing
    j = length(array)
    while j>1 && array[j-1] > array[j]
        array[j-1], array[j] = array[j], array[j-1]
        j -= 1
    end
end

"""Алгоритм вычисления среднего квадратического отклонения от среднего значения массива"""
function standard_deviation(A)
    Sx = 0
    Sx2 = 0
    for i in firstindex(A):lastindex(A)
        Sx += i
        Sx2 += i*i
    end
    return sqrt((Sx2 / length(A)) - ((Sx/ length(A))*(Sx/ length(A))))
end