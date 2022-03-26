-- Práctico 1

-- funciones por casos

-- 19

-- a

entre0y9 :: Int -> Bool
entre0y9 x | x > 9 = False
           | x < 0 = False
           | otherwise = True

-- b

rangoPrecio :: Int -> String
rangoPrecio x | x >= 5000 = "demasiado caro"
              | x < 0 = "esto no puede ser!"
              | x < 2000 = "muy barato"
              | otherwise = "hay que verlo bien"

-- c

absoluto :: Int -> Int
absoluto x | x < 0 = x * (-1)
           | otherwise = x

-- d

esMultiplo2 :: Int -> Bool
esMultiplo2 x | even x = True
              | otherwise = False



-- Combinando funciones

-- 20

esMultiploDe :: Int -> Int -> Bool
esMultiploDe x y | mod y x == 0 = True
                 | otherwise = False


-- 21

esBisiesto :: Int -> Bool
esBisiesto x | mod x 4 == 0 = True
             | otherwise = False


-- 22

dispersion :: Float -> Float -> Float -> Float
dispersion x y z = max x (max y z) / min x (min y z)


-- 23

celsiusToFahr :: Float -> Float
celsiusToFahr x = x * 1.8 + 32


-- 24

fahrToCelsius :: Float -> Float
fahrToCelsius x = (x - 32) / 1.8


-- 25

haceFrioF :: Float -> Bool
haceFrioF x | x < 8 = True
            | otherwise = False



-- tuplas

--26

-- a

segundo3 :: Num a => (a,a,a) -> a
segundo3 (_, a, _) = a

-- b

ordena :: Ord a => (a, a) -> (a, a)
ordena (x, y) | x > y = (y, x)
              | otherwise = (x, y)

-- c

rangoPrecioParametrizado :: (Num a, Ord a) => a -> (a, a) -> [Char]
rangoPrecioParametrizado x (menor, mayor) | x < 0 = "esto no puede ser!"
                                          | x < menor = "muy barato"
                                          | x > mayor = "demasiado caro"
                                          | otherwise = "hay que verlo bien"

-- d

--mayor3 :: (Int, Int, Int) -> (Bool, Bool, Bool)

-- e

todosIguales :: (Int, Int, Int) -> Bool
todosIguales (x,y,z) | x == y && x == z && y == z = True
                     | otherwise = False