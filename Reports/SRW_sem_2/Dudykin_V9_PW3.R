library("rlms")
library("lmtest")
library("dplyr")
library("GGally")
library("car")
library("sandwich")

ds <- rlms_read("r15i_os26c.sav")

data1 = select(ds, kj13.2, kh5, k_marst, k_educ, k_age, status, kj1.1.2, kj6.2, kj21.3,  kj23, kj32)

data1 = na.omit(data1)
glimpse(data)

#�������� c ���������� ������������
sal = as.numeric(data1$kj13.2)
sal1 = as.character(data1$kj13.2)
sal2 = lapply(sal1, as.integer)
sal = as.numeric(unlist(sal2))
mean(sal)
data1["salary"] = (sal - mean(sal)) / sqrt(var(sal))

#���
data1["sex"]=data1$kh5
data1["sex"] = lapply(data1["sex"], as.character)
data1$sex[which(data1$sex !='1')] <- 0
data1$sex[which(data1$sex =='1')] <- 1
data1$sex = as.numeric(data1$sex)

#�������� ���������
data1["wed"]= data1$k_marst
data1["wed"] = lapply(data1["wed"], as.character)
data1["wed1"]= data1$k_marst
data1$wed1 = 0
data1$wed1[which(data1$wed=='2')] <- 1
data1$wed1 = as.numeric(data1$wed1)

data1["wed2"]= data1$k_marst
data1$wed2 = 0
data1$wed2[which(data1$wed=='4')] <- 1
data1$wed2[which(data1$wed=='5')] <- 1
data1$wed2 = as.numeric(data1$wed2)

data1["wed3"]= data1$k_marst
data1$wed3 = 0
data1$wed3[which(data1$wed=='1')] <- 1
data1$wed3[which(data1$wed=='3')] <- 1
data1$wed3 = as.numeric(data1$wed3)

#������� ������� �����������
data1["h_educ"] = data1$k_educ
data1["h_educ"] = lapply(data1["h_educ"], as.character)
data1["higher_education"] = data1$k_educ
data1["higher_education"] = 0
data1$higher_education[which(data1$h_educ=='21')] <- 1
data1$higher_education[which(data1$h_educ=='22')] <- 1
data1$higher_education[which(data1$h_educ=='23')] <- 1

#������� c ���������� ������������
age1 = as.character(data1$k_age)
age2 = lapply(age1, as.integer)
age3 = as.numeric(unlist(age2))
data1["age"]= (age3 - mean(age3)) / sqrt(var(age3))

#���������� �����
data1["status1"]=data1$status
data1["status1"] = lapply(data1["status1"], as.character)
data1["city_status"] = 0
data1$city_status[which(data1$status1=='1')] <- 1
data1$city_status[which(data1$status1=='2')] <- 1
data1$city_status = as.numeric(data1$city_status)

#����������������� ��������� �����
data1["sat"]=data1$kj1.1.2
data1["sat"] = lapply(data1["sat"], as.character)
data1["satisfy"] = 0
data1$satisfy[which(data1$sat=='1')] <- 1
data1$satisfy[which(data1$sat=='2')] <- 1
data1$satisfy = as.numeric(data1$satisfy)

#����������������� ������� ������ � ���������� ������������
dur1 = as.character(data1$kj6.2)
dur2 = lapply(dur1, as.integer)
dur3 = as.numeric(unlist(dur2))
data1["duration"] = (dur3 - mean(dur3)) / sqrt(var(dur3))

#������� �� ������������, �� ������� �������� �������
data1["dan"] = data1$kj21.3
data1["dan"] = lapply(data1["dan"], as.character)
data1["dangerous"] = data1$kj21.3
data1["dangerous"] = 0
data1$dangerous[which(data1$dan=='1')] <- 1

#����������� - �������� ��� ���������� �����������
data1["gov"] = data1$kj23
data1["gov"] = lapply(data1["gov"], as.character)
data1["government"] = data1$kj23
data1["government"] = 0
data1$government[which(data1$gov=='1')] <- 1

#������� ������ ������
data1["w2"] = data1$kj32
data1["w2"] = lapply(data1["w2"], as.character)
data1["second_job"] = data1$kj32
data1["second_job"] = 0
data1$second_job[which(data1$w2=='1')] <- 1

data2 = select(data1, salary, sex, wed1, wed2, wed3, higher_education, age, city_status, satisfy, duration, dangerous, government, second_job)

#�������� ��������� �������� �� ��� ���������
model_test = lm(salary~sex+wed1+wed2+wed3+higher_education+age+city_status+satisfy+duration+dangerous+government+second_job, data2)
summary(model_test)
vif(model_test)
#R^2 ������ ����� ~21%. 3 "��������" � ����������� sex, higher_education, age, city_status, satisfy, duration, dangerous, government 
#p-���������� ���� ����������� ����. 0-1 "��������" � ����������� wed1, wed2, wed3, second_job.
#������ vif, ������ �����, ��� wed1, wed2, wed3 ������ ����� ��������, �������� ������ wed3 �� ������

model_test2 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+second_job, data2)
summary(model_test2)
vif(model_test2)
#R^2 ������ ������� ~21%. ������ �-���������� wed1 � wed2 ����������. ��������� second_job ����� ��������� salary. ������� ������� ��� ���������. 
#���������� vif � �������� 2, ������ ���� ���������� �� ����������� ����� �����.

model_original = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government, data2)
summary(model_original)
vif(model_original)
#R^2 ������ ����� ~21%. ����������� ����������� ������ ��������� ���� ��������� salary
#���������� vif � �������� 2, ������ ���� ���������� �� ����������� ����� �����.

#������������� �����������, ����� ��������, �������� ������� � ����������������� ������� ������,
#������������������ � ����

#���������
model1 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+log(age), data2)
summary(model1)
vif(model1)
#R^2 = 24.86%, vif �������� �� 3.5

model2 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+log(duration), data2)
summary(model2)
vif(model2)
#R^2 = 18.40%, vif �������� �� 4.5

model3 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+log(age)+log(duration), data2)
summary(model3)
vif(model3)
#R^2 = 23.51%, vif �������� �� 4.5
#model1 - ������ � �����������

#�������
model4 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^0.1), data2)
summary(model4)
vif(model4)
#R^2 = 24.8%, vif �������� �� 4.4
model5 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^0.1), data2)
summary(model5)
vif(model5)
#R^2 = 18.4%, vif �������� �� 5.7
model6 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^0.1)+I(duration^0.1), data2)
summary(model6)
vif(model6)
#R^2 = 23.43%, vif �������� �� 5.7

model7 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^0.2), data2)
summary(model7)
vif(model7)
#R^2 = 24.79%, vif �������� �� 5.9
model8 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^0.2), data2)
summary(model8)
vif(model8)
#R^2 = 18.4%, vif �������� �� 7.4
model9 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^0.2)+I(duration^0.2), data2)
summary(model9)
vif(model9)
#R^2 = 23.39%, vif �������� �� 7.3

model10 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^0.3), data2)
summary(model10)
vif(model10)
#R^2 = 24.77%, vif �������� �� 7.9
model11= lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^0.3), data2)
summary(model11)
vif(model11)
#R^2 = 18.4%, vif �������� �� 9.9
model12 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^0.3)+I(duration^0.3), data2)
summary(model12)
vif(model12)
#R^2 = 23.32%, vif �������� �� 9.8

model13 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^0.4), data2)
summary(model13)
vif(model13)
#R^2 = 24.75%, vif �������� �� 11.4
model14 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^0.4), data2)
summary(model14)
vif(model14)
#R^2 = 18.39%, vif �������� �� 13.9
model15 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^0.4)+I(duration^0.4), data2)
summary(model15)
vif(model15)
#R^2 = 23.25%, vif �������� �� 13.7

#�������, ��� ��� ���������� ������� ������ ����������� ����������� ���� �� �����
#����� ������������ R^2

model16 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^1.1), data2)
summary(model16)
vif(model16)
#R^2 = 24.64%, vif �������� �� 598
model17 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^1.1), data2)
summary(model17)
vif(model17)
#R^2 = 18.38%, vif �������� �� 598
model18 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^1.1)+I(duration^1.1), data2)
summary(model18)
vif(model18)
#R^2 = 22.77%, vif �������� �� 566

model19 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^1.5), data2)
summary(model19)
vif(model19)
#R^2 = 24.58%, vif �������� �� 29
model20 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^1.5), data2)
summary(model20)
vif(model20)
#R^2 = 18.38%, vif �������� �� 26
model21 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^1.5)+I(duration^1.5), data2)
summary(model21)
vif(model21)
#R^2 = 22.59%, vif �������� �� 28

#������ � ��������� 1.2-1.4 ���� ������� ��-�� ���������� �������� vif

model22 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^1.6), data2)
summary(model22)
vif(model22)
#R^2 = 24.57%, vif �������� �� 21
model23 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^1.6), data2)
summary(model23)
vif(model23)
#R^2 = 18.38%, vif �������� �� 19
model24 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^1.6)+I(duration^1.6), data2)
summary(model24)
vif(model24)
#R^2 = 22.56%, vif �������� �� 20.7

#������� ��������� �������� vif ��� ���������� ������� �� 1 �� 1.6
#�������� ����� � ������� 1.9

model25 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^1.9), data2)
summary(model25)
vif(model25)
#R^2 = 24.54%, vif �������� �� 10.8
model26 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^1.9), data2)
summary(model26)
vif(model26)
#R^2 = 18.38%, vif �������� �� 9
model27 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^1.9)+I(duration^1.9), data2)
summary(model27)
vif(model27)
#R^2 = 22.56%, vif �������� �� 10.7

model28 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^2), data2)
summary(model28)
vif(model28)
#R^2 = 22.92%, vif �� 1.6
model29= lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(duration^2), data2)
summary(model29)
vif(model29)
#R^2 = 21.18%, vif �� 1.6
model30 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+I(age^2)+I(duration^2), data2)
summary(model30)
vif(model30)
#R^2 = 22.9%, vif �������� �� 1.7

#������ ������ ����� ���������� - model1
#R^2 = 24.86%, ������� ����� ����������� ������� 
#������ ������ ����� ���� �������� - ��� model4(��������� age ���������� � ������� 0.1):
#R^2 = 24.8%, ������� ����� ����������� �������
#������ model1

model1 = lm(salary~sex+wed1+wed2+higher_education+age+city_status+satisfy+duration+dangerous+government+log(age), data2)
summary(model1)
vif(model1)

#������ ������������ ����� ��������� ������������ � model1:
sex: 0.4 - �������������
higher_education: 0.53 - �������������
age: -0.47 - �������������
city_status: 0.34 - �������������
satisfy: 0.35 - �������������
duration: 0.11 - �������������
dangerous: 0.22 - �������������
government: -0.19 - �������������
log(age): 0.11 - �������������
#����� � ���, ����� �������� �������� ������� ��������:
#������� �������� �������� � ����������� ���� �������, ���� � ������ ������������(��� ����� ������ ����������),
#������� ����, ����� ����, ����������� � ������, ��������, �������������� ������ ��������� �����. ��� ������� ��������
#�������� ����, ���������� �� ������� ��� ������� ������������� � ����, ���������� � ����������������� ���������, � ������� ����������� ����� � ������
#�������� ��������� �� ������ �� ������� ��.

#������������ ��������� �������, �� ��������� � �����
data3 = subset(data2, city_status == 1)
data3

data4 = subset(data3, wed1 == 0)
data4

model_subset1 = lm(data = data4, salary~sex+higher_education+age+satisfy+duration+dangerous+government+log(age))
summary(model_subset1)
vif(model_subset1)
#R^2 = 21.29%, ������������� ���������� dangerous, government, log(age); vif �������� (�� 3.5)
#����� ��������� ������� �� ��������� � ����� �� �� �� �������� �������� �������� ������ ������, � ���� ������������
#������� ������� ����������� ������ ��� ����� ������ ����(����������� ����� 0.67)

#������������ ����������� ������, � ������ ������������
data5 = subset(data2, wed2 == 1)
data5

data6 = subset(data5, sex == 0)
data6

data7 = subset(data6, higher_education == 1)
data7

model_subset2 = lm(data = data7, salary~age+city_status+satisfy+duration+dangerous+government+log(age))
summary(model_subset2)
vif(model_subset2)
#R^2 = 14.43% - ����� ���������, ��� ����������, ����� government �������������(� government 1 "��������"),
#vif �������� (�� 3.7). � ����������� ������ � ������ ������������ �������� �� ������� �� ������ �����������
