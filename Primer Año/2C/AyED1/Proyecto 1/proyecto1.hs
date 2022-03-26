-- ejercicio 1

-- a

esCero :: Int -> Bool
esCero n = n == 0

-- b

esPositivo :: Int -> Bool
esPositivo n = n > 0

-- c

esVocal :: Char -> Bool
esVocal a = a `elem` ['a', 'e', 'i', 'o', 'u']


-- ejercicio 2

-- a

paratodo :: [Bool] -> Bool
paratodo [] = True
paratodo (x:xs) = all (== True) xs

-- b

sumatoria :: [Int] -> Int
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria xs

-- c

productoria :: [Int] -> Int
productoria [] = 1
productoria (x:xs) = x * productoria xs

--d

factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n-1)

-- e

promedio :: [Int] -> Int
promedio [] = 0
promedio (x:xs) = sumatoria (x:xs) `div` length (x:xs)


-- ejercicio 3

pertenece :: Int -> [Int] -> Bool
pertenece _ [] = False
pertenece n (x:xs) = n `elem` (x:xs)


-- ejercicio 4

-- a

paratodo' :: [a] -> (a -> Bool) -> Bool
paratodo' [] _ = True
paratodo' (x:xs) t | t x = paratodo' xs t
                   | otherwise = False

-- b

existe' :: [a] -> (a -> Bool) -> Bool
existe' [] _ = False
existe' (x:xs) t | not (t x) = existe' xs t
                 | otherwise = True


-- c

sumatoria' :: [a] -> (a -> Int) -> Int
sumatoria' [] _ = 0
sumatoria' (x:xs) t = t x + sumatoria' xs t

-- d

productoria' :: [a] -> (a -> Int) -> Int
productoria' [] _ = 1
productoria' (x:xs) t = t x * productoria' xs t


-- ejercicio 5

paratodo'' :: [Bool] -> Bool
paratodo'' xs = paratodo' xs id


-- ejercicio 6

cmod :: Int -> Int -> Int
cmod x y = mod y x

-- a

todosPares :: [Int] -> Bool
todosPares xs = paratodo' xs even

-- b

hayMultiplo :: Int -> [Int] -> Bool
hayMultiplo n xs = existe' xs ((==0) . cmod n)

-- c

sumaCuadrados :: Int -> Int
sumaCuadrados n = sumatoria' [0..n] (^2)

-- d

factorial' :: Int -> Int
factorial' n = productoria [1..n]

-- e

multiplicaPares :: [Int] -> Int
multiplicaPares xs = productoria (filter even xs)


-- ejercicio 7

-- a

-- La función map aplica la función indicada a cada uno de los elementos de la lista.
-- map :: (a -> b) -> [a] -> [b]

-- La función filter evalua en cada elemento si cumple las condiciones que la función proporcionada
-- brinda, para así ir armando una lista nueva con los elementos filtrados.
-- filter :: (a -> Bool) -> [a] -> [a]

-- b

-- [2, -3, 7, 3, -7]

-- c

-- [1,6,2]


-- ejercicio 8

-- a

duplica :: [Int] -> [Int]
duplica [] = []
duplica (x:xs) = x*2: duplica xs

-- b

duplica' :: [Int] -> [Int]
duplica' [] = []
duplica' xs = map (* 2) xs


-- ejercicio 9

-- a

soloPares :: [Int] -> [Int]
soloPares [] = []
soloPares (x:xs) | even x = x: soloPares xs
                 | otherwise = soloPares xs

-- b

soloPares' :: [Int] -> [Int]
soloPares' [] = []
soloPares' xs = filter even xs


-- c


-- ejercicio 10

-- a

primIgualesA :: Eq a => a -> [a] -> [a]
primIgualesA _ [] = []
primIgualesA n (x:xs) = if x == n then x: primIgualesA n xs else []

-- b

primIgualesA' :: Eq a => a -> [a] -> [a]
primIgualesA' _ [] = []
primIgualesA' n xs = takeWhile (==n) xs


-- ejercicio 11

-- a

primIguales :: Eq a => [a] -> [a]
primIguales [] = []
primIguales [x] = [x]
primIguales (x:xs) = if x == head xs then x: primIguales xs else [x]


-- b

primIguales' :: Eq a => [a] -> [a]
primIguales' [] = []
primIguales' [x] = [x]
primIguales' xs = primIgualesA (head xs) xs