function newton(r::Function, x_0, epsilon = 1e-8, ttl = 20)
    x_prev = x_0 - r(x_0)
    while(abs(x_prev) > epsilon)
        if ttl == 0
            return print("ERROR: x_0 is bad")
        end
        x_prev = x_prev - r(x_prev)
    end
    return x_prev
end
