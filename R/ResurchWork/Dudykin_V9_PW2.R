library("lmtest")
library("car")

data = mtcars
help(mtcars)
data

#�������� ���������� �������� ����������� ����� ������������
modela = lm(wt~qsec+hp+drat, data)
modelb = lm(qsec~wt+hp+drat, data)
modelc = lm(hp~wt+qsec+drat, data)
modeld = lm(drat~wt+qsec+hp, data)
summary(modela)
summary(modelb)
summary(modelc)
summary(modeld)
#R^2 � modela ����� 69.1% - �������; R^2 � modelb ����� 61.51% - �������, R^2 � modelc ����� 77.51% - ����� �������
#R^2 � modeld ����� 45.61% - �������. ��������� hp ����� ������ � ����������, �������� ��� �� ������.

modele = lm(wt~qsec+drat, data)
modelf = lm(qsec~wt+drat, data)
modelg = lm(drat~wt+qsec, data)
summary(modele)
summary(modelf)
summary(modelg)
#��� ����� � ������� R^2 ����� 48.66%, 3.28% � 47.49% - �� ����� ������� ��� ��� ������, ����� �������� 
#������ � ����� ������������

modelmain = lm(mpg~wt+qsec+drat, data)
summary(modelmain)
vif(modelmain)
#1)����������� ������������ R^2 ����� 81.96%, ��� ��� ����� �������� ������, R^2 �������
#2)P-�������� ���������� wt ����� ����(5.01�-07), ��� ������. � ����������� qsec � drat ��� ������(0.001 � 0.19).
#� wt 3 ��������, � qsec 2 ��������, � � ���������� drat �� ���. � ���� ����������� ���������� ������ ����������
#������, � �������� � ���������� drat(��� ����� 1.23), ������ ����� ������ drat �������� ���������� � ������
#vif � ������� ������������ ��������� � �������� �� 1.03 �� 2.08, ��� ������� � ������������� �����������.

#������ ��� �������� ���������� drat �� ������ R^2 ������ ����� �� 0.5%. � "������" ������� ��� ������ �� �������.

#�������� ������ � ����������� ����������.
model1 = lm(mpg~wt+qsec+drat+log(wt), data)
summary(model1)
vif(model1)
#R^2 = 86.71% - ��� ������ ������ �����  ������� � ������������ ����������� �� �����������
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

#�������� ������ � ����������� ��������� ����������� 
model8 = lm(mpg~wt+qsec+drat+I(wt^2), data)
summary(model8)
vif(model8)
#R^2 = 86.55% - ��� ������ ������ �����  ������� � ������������ ���������� �����������
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

#�������� ������ � ����������� ������������ ��� �����������
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
#R^2 = 84.33% - ��� ������ ������ �����  ������� � ������������ �������������� ��� �����������
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

#������� ������ ������ ����� ��������� ����
model17 = lm(mpg~wt+qsec+drat+I(drat*wt), data)
summary(model17)
vif(model17)
#vif � ���������� wt ����� ~53.6, ����� ��� �� ������
modelfinal = lm(mpg~qsec+drat+I(drat*wt), data)
summary(modelfinal)
vif(modelfinal)
#R^2 = 84.46% � ������������ vif �� ��������� 1.18, � ���� ����������� ���� ��������,
#������ ��� ������ ������ �� ������ ��������� � ����� �������

#����� ������������� ��������� ��� ������������� ����������� � ������� ����� �� ���������� ��� ������������� ���������� ��������������
#�������� � ���, ��� ����������� ����� 0
t_critical = qt(0.975, df = 28)
#t_critical = 2.048407

#������������� �������� ��� ������������ ���������� qsec [0.89-2.05*0.24;0.89+2.05*0.24] = [0.4;1.38]
#���� �� ������ � ������������� �������� ������������ ����� �����������, � ������ mpg ������� �� qssec

#������������� �������� ��� ������������ ���������� drat [5.19-2.05*0.85;5.19+2.05*0.85] = [3.45;6.93]
#���� �� ������ � ������������� �������� ������������ ����� �����������, � ������ mpg ������� �� drat

#������������� �������� ��� ������������ ���������� I(drat * wt) [-1.33-2.05*0.18;-1.33+2.05*0.18] = [-1.7;-0.96]
#���� �� ������ � ������������� �������� ������������ ����� �����������, � ������ mpg ������� �� I(drat * wt)

new.data = data.frame(qsec= 17.5,drat = 4, wt = 3.4)
predict(modelfinal, new.data, interval = "confidence")
#    fit       lwr      upr
#1 18.69864 17.13805 20.25923














