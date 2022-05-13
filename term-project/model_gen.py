import joblib
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVR
from sklearn.gaussian_process import GaussianProcessClassifier

import pandas as pd


# Load and combine all training samples
# df = pd.read_csv("sample_f1.csv")
df = pd.read_csv("sample1-1.csv")

# df = df.append(pd.read_csv("sample1-1.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-2.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-3.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-4.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-5.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-6.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-7.csv"), ignore_index=True)

df = df.append(pd.read_csv("sample1-8.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-9.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-10.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-11.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-12.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-13.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-14.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample1-15.csv"), ignore_index=True)

# df = pd.read_csv("sample_f4.csv")

df = df.append(pd.read_csv("sample2-1.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-2.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-3.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-4.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-5.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-6.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-7.csv"), ignore_index=True)

df = df.append(pd.read_csv("sample2-8.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-9.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-10.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-11.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-12.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-13.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-14.csv"), ignore_index=True)
df = df.append(pd.read_csv("sample2-15.csv"), ignore_index=True)

# Preprocessing
df = df.drop("Unnamed: 0", axis=1)
X = df[["r1", "r2", "p1", "p2"]]
y = df[["gesture"]]
print(X)
print(y)



# Fitting models
lr = LinearRegression()
lr.fit(X, y)

llr = LogisticRegression()
llr.fit(X, y)

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X, y)

dtcg = DecisionTreeClassifier(criterion="gini")
dtcg.fit(X, y)

dtce = DecisionTreeClassifier(criterion="entropy")
dtce.fit(X, y)

svr = SVR(C=1, epsilon=0.1)
svr.fit(X, y)

# gp = GaussianProcessClassifier()
# gp.fit(X, y)


# Get model's score
scores = lr.score(X, y)
print(lr)
print(scores)

scores = llr.score(X, y)
print(llr)
print(scores)

scores = knn.score(X, y)
print(knn)
print(scores)

scores = dtcg.score(X, y)
print(dtcg)
print(scores)

scores = dtce.score(X, y)
print(dtce)
print(scores)

scores = svr.score(X, y)
print(svr)
print(scores)

# scores = gp.score(X, y)
# print(gp)
# print(scores)


print("===========")

# Result score
# # Linear Reg.
# 0.5004092880674549
# # Logistic Reg.
# 0.9678188319427891
# # kNN
# 0.9976162097735399
# # Decision Tree Classifier gini
# 1.0
# # Decision Tree Classifier entropy
# 1.0



# Save model to serialized file
saved_model = joblib.dump(svr, "sample.pkl")
print(saved_model)
