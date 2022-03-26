sumar1 :: Int -> Int
sumar1 x = x + 1

prom :: Fractional a => a -> a -> a
prom x y = (x + y) / 2

-- recursion

sumatoria :: [Int] -> Int
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria xs

sumatoria1 :: [Int] -> Int
sumatoria1 = sum

-- x

--mas :: [a] -> [a] -> [a]
--[] mas ys = ys
--(x:xs) = x: xs mas ys


qEquation :: (Float, Float, Float) -> (Float, Float)
qEquation (a, b, c) = (x1, x2)
		where
			x1 = e + sqrt d / (2 * a)
			x2 = e - sqrt d / (2 * a)
			d = b * b - 4 * a * c
			e = - b / (2 * a)