library("lmtest")

data = swiss
help(swiss)
data

#1.��������� ������� ��������, ��������� � ��� ���������� Examination,Education � Infant.Mortality.

mean(data$Examination)
#������� �������� ����� 16.49, �� ����� ���� ����� ������ ������ �� �������, ���������������� ����������� � �������� 
#����� ������������

mean(data$Infant.Mortality) 
#������� �������� ����� 19.94, �� ���� � ������� ������ ����� ������ ������ �� ����, �������� �����
#������ ��������� ������� 

mean(data$Education) 
#������� �������� ����� 10.98, �� ���� ������ 11% ������� �������� ����������� ���� ������ ���������
#����� ��� �����������, ��� ������ ���� � ��������� � �������� ����� �����


#�������� ������������ 
data["Examination1"] = data$Examination - mean(data$Examination)
data["Education1"] = data$Education - mean(data$Education)
data["Infant.Mortality1"] = data$Infant.Mortality - mean(data$Infant.Mortality)


#������������� ������
data["Examination2"] = (data$Examination - mean(data$Examination))/sqrt(var(data$Examination))
data["Education2"] = (data$Education - mean(data$Education))/sqrt(var(data$Education))
data["Infant.Mortality2"] = (data$Infant.Mortality - mean(data$Infant.Mortality))/sqrt(var(data$Infant.Mortality))

plot(data$Examination2) + abline(a = 0, b = 0, col = "red")
#����� ������ ������� ��������, �������� �������� ������ ��������(������� �� 2-�� ����������� ����������), � ������
#�������� ������ ��������(���� �� 2-�� ����������� ����������, ������� ��� �������� � ����������� ���� ���� 2-��)
#� ������ ���������� �������� ���� �������� ������ ��-�������, ��� ���� ���������� ������ ���� �������� ���� ������

plot(data$Infant.Mortality2) + abline(a = 0, b = 0, col = "blue")
#��� ��������, ����� ������, �� ��������� 2-�� ����������� ����������(���� �������� ���������� ������ ��� �� 2 
#����������). �� ������ �������� ��������� �����

plot(data$Education2) + abline(a = 0, b = 0, col = "green")
#������� ����� �������� ������ �������� � ��������� �� ���� �� ������, �� ���� � 
#������������ ��������(������� ��������), ������������ �� �������� �� 2 � ����� ����������� ����������
#������ ����������� ���������  ��������, �� � ����������� ������� �� ���


#2. ������ ����������� � ��������� ��.

model1 = lm(Examination~Education, data)
model1
summary(model1)
plot(data$Examination, data$Education) + abline(a = 10.13, b = 0.58, col = "red")
#����������� ������������ R^2 ����� 48.78%, ��� ���������� ����� ��� ������ � ����� �����������, ������ ������ � �� 
#������ �������, ���-�� ��� ������ � data �� ����� ������. p-���������� ����� 4.81e-08, � ������ � ���������� ��� 
#��� ��������, ��� ������, ��� ���������� Examination � Education ������ ������� ����� �����.

model2 = lm(Examination~Infant.Mortality, data)
model2
summary(model2)
plot(data$Examination, data$Infant.Mortality) + abline(a = 22.72, b = -0.31, col = "red")
#����������� ������������ R^2 ����� 1.3%, ��� ��� ��� ����� ����, ������ ����������� "�����", ��� �� ��� ��� 
#�������� ������������� � ����������� ������ � data. p-���������� ����� 0.45(���������, ��� ���� �����), �������� 
#� ������ � ���������� ���, ������ ����������� ����� Examination � Infant.Mortality ����������� ���.
