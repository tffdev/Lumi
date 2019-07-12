

x = math.random(356)
y = math.random(356)

function init()
    printf("init!!!!!!!!!!!!!!!!! x[%i] y[%i] (objTest) _ENV [%s]", x, y, _ENV)
end

function update()
    x = x + 1
end

function draw()
    draw_square(x, y)
end