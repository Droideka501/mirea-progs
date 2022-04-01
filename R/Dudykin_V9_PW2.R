library("lmtest")
library("car")

data = mtcars
help(mtcars)
data

#проверим отсутствие линейной зависимости между регрессорами
modela = lm(wt~qsec+hp+drat, data)
modelb = lm(qsec~wt+hp+drat, data)
modelc = lm(hp~wt+qsec+drat, data)
modeld = lm(drat~wt+qsec+hp, data)
summary(modela)
summary(modelb)
summary(modelc)
summary(modeld)
#R^2 в modela равен 69.1% - высокий; R^2 в modelb равен 61.51% - высокий, R^2 в modelc равен 77.51% - очень высокий
#R^2 в modeld равен 45.61% - средний. Регрессор hp очень связан с остальными, исключим его из модели.

modele = lm(wt~qsec+drat, data)
modelf = lm(qsec~wt+drat, data)
modelg = lm(drat~wt+qsec, data)
summary(modele)
summary(modelf)
summary(modelg)
#Вот здесь в моделях R^2 равен 48.66%, 3.28% и 47.49% - не такой высокий как был раньше, будем работать 
#дальше с этими регрессорами

modelmain = lm(mpg~wt+qsec+drat, data)
summary(modelmain)
vif(modelmain)
#1)Коэффициент детерминации R^2 равен 81.96%, это уже очень неплохая модель, R^2 высокий
#2)P-значения регрессора wt очень мало(5.01е-07), это хорошо. У регрессоров qsec и drat уже больше(0.001 и 0.19).
#У wt 3 звёздочки, у qsec 2 звёздочки, а у регрессора drat их нет. У всех регрессоров достаточно велика стандатная
#ошибка, а особенно у регрессора drat(она равна 1.23), скорее всего именно drat наиболее незначимый в модели
#vif у каждого коэффициента находится в пределах от 1.03 до 2.08, что говорит о независимости регрессоров.

#Вообще при удалении регрессора drat из модели R^2 падает всего на 0.5%. В "боевых" услових его стоило бы удалить.

#Построим модели с добавлением логарифмов.
model1 = lm(mpg~wt+qsec+drat+log(wt), data)
summary(model1)
vif(model1)
#R^2 = 86.71% - это лучшая модель среди  моделей с добавленными логарифмами от регрессоров
model2 = lm(mpg~wt+qsec+drat+log(qsec), data)
summary(model2)
vif(model2)
#R^2 = 83.03%
model3 = lm(mpg~wt+qsec+drat+log(drat), data)
summary(model3)
vif(model3)
#R^2 = 81.36%
model4 = lm(mpg~wt+qsec+drat+log(wt)+log(qsec), data)
summary(model4)
vif(model4)
#R^2 = 86.41%
model5 = lm(mpg~wt+qsec+drat+log(qsec)+log(drat), data)
summary(model5)
vif(model5)
#R^2 = 82.38%
model6 = lm(mpg~wt+qsec+drat+log(wt)+log(drat), data)
summary(model6)
vif(model6)
#R^2 = 86.45%
model7 = lm(mpg~wt+qsec+drat+log(wt)+log(qsec)+log(drat), data)
summary(model7)
vif(model7)
#R^2 = 86.2%

#Построим модели с добавлением квадратов регрессоров 
model8 = lm(mpg~wt+qsec+drat+I(wt^2), data)
summary(model8)
vif(model8)
#R^2 = 86.55% - это лучшая модель среди  моделей с добавленными квадратами регрессоров
model9 = lm(mpg~wt+qsec+drat+I(qsec^2), data)
summary(model9)
vif(model9)
#R^2 = 83%
model10 = lm(mpg~wt+qsec+drat+I(drat^2), data)
summary(model10)
vif(model10)
#R^2 = 81.39%
model11 = lm(mpg~wt+qsec+drat+I(wt^2)+I(qsec^2), data)
summary(model11)
vif(model11)
#R^2 = 86.24%
model12 = lm(mpg~wt+qsec+drat+I(qsec^2)+I(drat^2), data)
summary(model12)
vif(model12)
#R^2 = 82.35%
model13 = lm(mpg~wt+qsec+drat+I(wt^2)+I(drat^2), data)
summary(model13)
vif(model13)
#R^2 = 86.14%
model14 = lm(mpg~wt+qsec+drat+I(wt^2)+I(qsec^2)+I(drat^2), data)
summary(model14)
vif(model14)
#R^2 = 85.86%

#Построим модели с добавлением произведений пар регрессоров
model15 = lm(mpg~wt+qsec+drat+I(wt*qsec), data)
summary(model15)
vif(model15)
#R^2 = 81.84%
model16 = lm(mpg~wt+qsec+drat+I(qsec*drat), data)
summary(model16)
vif(model16)
#R^2 = 82.07%
model17 = lm(mpg~wt+qsec+drat+I(drat*wt), data)
summary(model17)
vif(model17)
#R^2 = 84.33% - это лучшая модель среди  моделей с добавленными произведениями пар регрессоров
model18 = lm(mpg~wt+qsec+drat+I(wt*qsec)+I(qsec*drat), data)
summary(model18)
vif(model18)
#R^2 = 81.52%
model19 = lm(mpg~wt+qsec+drat+I(qsec*drat)+I(drat*wt), data)
summary(model19)
vif(model19)
#R^2 = 84.17%
model20 = lm(mpg~wt+qsec+drat+I(wt*qsec)+I(drat*wt), data)
summary(model20)
vif(model20)
#R^2 = 84.08%
model21 = lm(mpg~wt+qsec+drat+I(wt*qsec)+I(qsec*drat)+I(drat*wt), data)
summary(model21)
vif(model21)
#R^2 = 83.65%

#Выберем лучшую модель среди абсолютно всех
model17 = lm(mpg~wt+qsec+drat+I(drat*wt), data)
summary(model17)
vif(model17)
#vif у регрессора wt равен ~53.6, уберём его из модели
modelfinal = lm(mpg~qsec+drat+I(drat*wt), data)
summary(modelfinal)
vif(modelfinal)
#R^2 = 84.46% и коэффициенты vif не превышают 1.18, у всех регрессоров есть звёздочки,
#значит это лучшая модель из вообще возможных с этими данными

#Найдём доверительные интервалы для коэффициентов регрессоров и сделаем вывод об отвержении или невозможности отвергнуть статистическую
#гипотезу о том, что коэффициент равен 0
t_critical = qt(0.975, df = 28)
#t_critical = 2.048407

#Доверительный интервал для коэффициента регрессора qsec [0.89-2.05*0.24;0.89+2.05*0.24] = [0.4;1.38]
#Ноль не входит в доверительный интервал коэффициента перед регрессором, а значит mpg зависит от qssec

#Доверительный интервал для коэффициента регрессора drat [5.19-2.05*0.85;5.19+2.05*0.85] = [3.45;6.93]
#Ноль не входит в доверительный интервал коэффициента перед регрессором, а значит mpg зависит от drat

#Доверительный интервал для коэффициента регрессора I(drat * wt) [-1.33-2.05*0.18;-1.33+2.05*0.18] = [-1.7;-0.96]
#Ноль не входит в доверительный интервал коэффициента перед регрессором, а значит mpg зависит от I(drat * wt)

new.data = data.frame(qsec= 17.5,drat = 4, wt = 3.4)
predict(modelfinal, new.data, interval = "confidence")
#    fit       lwr      upr
#1 18.69864 17.13805 20.25923














