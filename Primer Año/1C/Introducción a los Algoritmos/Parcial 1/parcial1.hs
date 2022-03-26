-- 1)

pegarEn3 :: [(String, String)] -> [(String, String, String)]
pegarEn3 [] = []
pegarEn3 ((x,y):xs) = (x,y, x ++ y): pegarEn3 xs


-- 2)

cocientes :: Int -> [Int] -> [Int]
cocientes n [] = []
cocientes n (x:xs) = (x `div` n):(cocientes n xs)


-- 3)

