function searchsorted_last()
end

function searchsorted_first(A, x)
    average = Int((first(A)+last(A))/2+1)
    if x < A[average] return searchsorted_first(A[1, average], x) end
    if x > A[average] return searchsorted_first(A[average, last(A)], x) end
    if x == A[average] return A[average] end
end