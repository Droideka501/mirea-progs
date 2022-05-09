library("lmtest")

data = swiss
help(swiss)
data

#1.Оцениваем средние значения, дисперсии и СКО переменных Examination,Education и Infant.Mortality.

mean(data$Examination)
#среднее значение равно 16.49, на самом деле очень низкая оценка за экзамен, подготовленность призывников к экзамену 
#очень сомнительная

mean(data$Education) 
#среднее значение равно 10.98, то есть только 11% человек получало образование выше уровня начальной
#школы для призывников, это крайне мало в сравнении с реалиями нашей жизни

mean(data$Infant.Mortality) 
#среднее значение равно 19.94, то есть в среднем каждый пятый ребёнок умирал до года, медицина тогда
#желала оставлять лучшего 

#элементы нормализации 
data["Examination1"] = data$Examination - mean(data$Examination)
data["Education1"] = data$Education - mean(data$Education)
data["Infant.Mortality1"] = data$Infant.Mortality - mean(data$Infant.Mortality)


#предобработка данных
data["Examination2"] = (data$Examination - mean(data$Examination))/sqrt(var(data$Examination))
data["Education2"] = (data$Education - mean(data$Education))/sqrt(var(data$Education))
data["Infant.Mortality2"] = (data$Infant.Mortality - mean(data$Infant.Mortality))/sqrt(var(data$Infant.Mortality))

plot(data$Examination2) + abline(a = 0, b = 0, col = "red")
#здесь полный разброс значений, примерно половина меньше среднего(разница до 2-ух стандартных отклонений), а другая
#половина больше среднего(тоже до 2-ух стандартных отклонений, включая два значения с отклонением чуть выше 2-ух)
#В разных провинциях экзамены были написаны совсем по-разному, при этом количество оценок ниже среднего чуть больше

plot(data$Education2) + abline(a = 0, b = 0, col = "green")
#большее число значений меньше среднего и отклонены от него не сильно, но есть и 
#выделяющиеся значения(большие среднего), отличающиеся от среднего на 2 и более стандартных отклонения
#Уровни образования провинций  различны, но в большинстве случаев он мал

plot(data$Infant.Mortality2) + abline(a = 0, b = 0, col = "blue")
#все значения, кроме одного, не превышают 2-ух стандартных отклонений(одно значение отличается больше чем на 2 
#отклонения). По уровню медицины провинции схожи

#2. Строим зависимости и оцениваем их.

model1 = lm(Examination~Education, data)
model1
summary(model1)
plot(data$Examination, data$Education) + abline(a = 10.13, b = 0.58, col = "red")
#Коэффициент детерминации R^2 равен 48.78%, это достаточно много для модели с одним регрессором, данную модель я бы 
#назвал средней, что-то про данные в data мы можем понять. p-статистика равна 4.81e-08, в модели у регрессора все 
#три звёздочки, это значит, что переменные Examination и Education сильно связаны между собой.

model2 = lm(Examination~Infant.Mortality, data)
model2
summary(model2)
plot(data$Examination, data$Infant.Mortality) + abline(a = 22.72, b = -0.31, col = "red")
#Коэффициент детерминации R^2 равен 1.3%, вот это уже очень мало, модель чрезвычайно "плоха", она не даёт нам 
#никакого представления о зависимости данных в data. p-статистика равна 0.45(многовато, это тоже плохо), звёздочек 
#в модели у регрессора нет, значит взаимосвязи между Examination и Infant.Mortality практически нет.
