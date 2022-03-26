-- 2)

-- a)

sum_cuad :: [Int] -> Int
sum_cuad [] = 0
sum_cuad (x:xs) = x*x + sum_cuad xs

-- d)

sum_par :: Int -> Int
sum_par 0 = 0
sum_par n = sum_par (n-1)