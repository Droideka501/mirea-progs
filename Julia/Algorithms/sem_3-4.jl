
"""Перестановка двух элементов"""
function swap!(array::AbstractVector, i, j)
    temp = array[i]
    array[i] = array[j]
    array[j] = temp
end

"""Сортировка вставками"""
function insertionSort!(array::AbstractVector)
    for i in 2:length(array)
        for j in i-1:-1:1
            if array[i] < array[j]
                swap!(array, i, j)
            end
        end
    end
end

"""Сортировка Шелла"""
#function shellSort!(array::AbstractVector)
#    gap = length(array)
#    while gap > 0
#        for i in 1:lastindex(array)-gap
#            insertionSort!(@view array[i:gap:lastindex(array)])
#        end
#        gap = div(gap, 2)
#    end
#end

"""Сортировка Шелла более оптимизированная"""
function shellSort!(array::AbstractVector)
    gap = length(array)
    while gap > 0
        for i in 1:lastindex(array)-gap
            j = i
            while j >= firstindex(a) && array[j] > array[j+gap]
                swap!(array, j, j+gap)
                j -= gap
            end
        end
        gap = div(gap, 2)
    end
end

"""Поиск всех максимальных значений массива"""
function findAllMax(array::AbstractVector)
    index_max = Vector{Int}(undef, length(array))
    index_max[begin] = firstindex(array)
    j = 1
    for i in 1:length(array)
        if array[i] > array[index_max[begin]]
            index_max[begin] = i
            j = 1
        elseif array[i] == array[index_max[begin]]
            index_max[begin+j] = i
            j+=1
        end
    end
    return index_max[1:j]
end

"""Сортировка пузырьком (последние i элементов всегда будут отсортированы, поэтому вложенный цикл до len - i элементов)"""
function bubbleSortModF!(array::AbstractVector)
    for i in 1:length(array)
        for j in 1:length(array)-i
            if array[j] > array[j+1]
                swap!(array, j, j+1)
            end
        end
    end
end


"""Сортировка пузырьком (двухсторонняя)"""
function bubbleSortModS!(array::AbstractVector)
    counter = 0
    start = 2
    stop = length(array)-1
    step = 1
    for i in 1:(length(array)/2+1)
        for j in start:step:stop
            if step == 1
                if array[j] > array[j+step]
                    swap!(array, j, j+step)
                end
            end
            if step == -1
                if array[j] < array[j+step]
                    swap!(array, j, j+step)
                end
            end
        end
        if step == 1
            stop -= 1
        elseif step == -1
            start += 1
        end
        step = -step
        temp = start
        start = stop
        stop = temp
    end
end


"""Реализация среза"""
function slice(A::AbstractVector, p::AbstractVector{<:Integer})
    temp = typeof(A)()
    for i in p
        push!(temp, A[i])
    end
    return temp
end

"""Перестановки с негативом изначального массива"""
function permute_!(A::AbstractVector, perm::AbstractVector{<:Integer})
    first = 1
    itr_up = first
    temp_1 = A[first]
    itr_low = perm[itr_up]
    while any(x > 0 for x in perm)
        while itr_low != first
            itr_low = perm[itr_up]
            temp_2 = A[itr_low]
            A[itr_low] = temp_1
            temp_1 = temp_2
            perm[itr_up] = -perm[itr_up]
            itr_up = itr_low
        end
        for i in perm
            if i > 0
                first = i
                break
            end
        end
    end
end

"""Вставка элемента в массив по индексу"""
function insertAt!(A::AbstractVector, index::Integer, value::Real)
    push!(A, value)
    for i in length(A):-1:index+1
        swap!(A, i, i-1)
    end
    return A
end

""""""
function deleteAt!(A::AbstractVector, index::Integer)
    for i in index:length(A)-1
        swap!(A, i, i+1)
    end
    pop!(A)
    return A
end

""""""
function unique_(A::AbstractVector)
    B = []
    sort!(A)
    push!(B, A[1])
    for i in 2:lenght(A)
        if A[i] != A[i-1]
            push!(B, A[i])
        end
    end
    return B
end

""""""
function unique_!(A::AbstractVector)
    sort!(A)
    for i in 2:lenght(A)
        if A[i] == A[i-1]
            deleteAt!(A, i)
        end
    end
    return A
end

""""""
function AllUnique_(A::AbstractVector)
    sort!(A)
    for i in 2:lenght(A)
        if A[i] == A[i-1]
            return false
        end
    end
    return true
end

""""""
function Reverse!(A::AbstractVector, k::Integer = 0)
    for i in 1:div(length(A)-k, 2)
        swap!(A, i, length(A)-i+1)
    end
    return A
end

""""""
function circleShift!(A::AbstractVector, k::Integer)
    k = k%length(A)
    Reverse!(A)
    Reverse!(@view A[begin:k])
    Reverse!(@view A[begin+k:end])

    return A
end

""""""
function transposeFirstMod!(A::AbstractMatrix)
    for i in 1:lenght(A[1])
        temp = deepcopy(A[i, :])
        A[i, :] = deepcopy(A[:, i])
        A[:, i] = temp
    end
    return A
end
