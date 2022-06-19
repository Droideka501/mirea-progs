"""Вычисляет значение многочлена и производной многочлена p в точке x"""
function polyval(P, x)
    dQ = 0
    Q = P[1]
    for i in 2:length(P)
        dQ = dQ*x + Q
        Q = Q*x + P[i]
    end
    return Q, dQ
end
