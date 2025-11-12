import math

def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def tsp(points):
    n = len(points)

    dist = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            dist[i][j] = distance(points[i], points[j])
    
    # dp[mask][i] = стоимость, чтобы достичь этого состояния, i - город, в котором находимся на данный момент
    dp = [[float('inf')] * n for _ in range(2**n)]
    dp[1][0] = 0  # Начало из города 0 с маской 001 (только первый город посещен)
    
    # DP таблица
    for mask in range(2**n):
        for i in range(n):
            if dp[mask][i] == float('inf'): # пропускаем все невозможные состояния
                continue
            # Рассматриваем всевозможные следующие города, в которые можно попасть из i
            for j in range(n):
                if mask & (2**j):  # побитовое сравнение текущей маски и маски города j, чтобы понять посещен ли город j (если НЕ 0 => посещен)
                    continue # пропускаем итерацию, если город уже посещен, тк не можем посетить повторно
                new_mask = mask | (2**j) # добавляем город j в нашу маску с помощью ИЛИ
                dp[new_mask][j] = min(dp[new_mask][j], dp[mask][i] + dist[i][j]) # ищем кратчайшипй путь, который приводит к этому состоянию
    
    # Поиск минимального пути с возвратом в стартовый город
    ans = float('inf')
    for i in range(n):
        ans = min(ans, dp[(2**n) - 1][i] + dist[i][0])
    
    return ans

points = [
    (0, 0),
    (2, 2),
    (3, 1),
    (1, 3)
]

print("Минимальная длина пути:", tsp(points))

