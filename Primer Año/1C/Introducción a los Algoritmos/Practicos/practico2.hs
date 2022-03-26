-- Práctico 2

-- 3

-- a

soloPares :: [Int] -> [Int]
soloPares [] = []
soloPares (x:xs) | even x = x: soloPares xs
                 | otherwise = soloPares xs

-- b

mayoresQue10 :: [Int] -> [Int]
mayoresQue10 [] = []
mayoresQue10 (x:xs) | x > 10 = x: mayoresQue10 xs
                    | otherwise = mayoresQue10 xs

-- c

mayoresQue :: Int -> [Int] -> [Int]
mayoresQue n [] = []
mayoresQue n (x:xs) | x > n = x: mayoresQue n xs
                    | otherwise = mayoresQue n xs


-- 4

-- a

sumar1 :: [Int] -> [Int]
sumar1 [] = []
sumar1 (x:xs) = x+1: sumar1 xs

-- b

duplica :: [Int] -> [Int]
duplica [] = []
duplica (x:xs) = (x*2): duplica xs

-- c

multiplica :: Int -> [Int] -> [Int]
multiplica _ [] = []
multiplica n (x:xs) = x*n: multiplica n xs


-- 5

miFold :: (a -> Bool) -> [a] -> Bool
miFold _ [] = True
miFold f (x:xs) | f x = miFold f xs
                | otherwise = False

-- a

todosMenores10 :: [Int] -> Bool
todosMenores10 = miFold (<10)

-- b

nohay0 :: [Int] -> Bool
nohay0 = miFold (/=0)
hay0 :: [Int] -> Bool
hay0 xs = not (nohay0 xs)

-- c

sum1 :: [Int] -> Int
sum1 [] = 0
sum1 (x:xs) = x + sum1 xs


-- 6

fZip :: [a] -> [b] -> [(a, b)]
fZip (x:xs) [] = []
fZip [] (x:xs) = []
fZip (x:xs) (y:ys) = (x, y): fZip xs ys


-- 7

apellidos :: [(String, String, Int)] -> [String]
apellidos [] = []
apellidos ((_,n,_):xs) = n: apellidos xs


-- 8

-- lenght xs

longitud :: [a] -> Int
longitud [] = 0
longitud (x:xs) = 1 + longitud xs

-- xs !! n (index)

indice :: [a] -> Int -> a
indice (x:xs) n | n == 0 = x
                | otherwise = indice xs (n-1)

-- head

head1 :: [a] -> a
head1 (x:xs) = x

-- tail

tail1 :: [a] -> [a]
tail1 (x:xs) = tail1 xs

-- concat

concat1 :: [a] -> [a] -> [a]
concat1 [] ys = ys
concat1 xs ys = concat1 (take (length xs -1) xs) (drop (length xs -1) xs `indice` 0: ys)


-- 10


-- 12

quitarCeros :: [Int] -> [Int]
quitarCeros [] = []
quitarCeros (x:xs) | x /= 0 = x:quitarCeros xs
                   | x == 0 = quitarCeros xs




-- 20

-- a)

listasIguales :: Eq a => [a] -> [a] -> Bool
listasIguales [] [] = True
listasIguales (x:xs) (y:ys) | x:xs == y:ys = True
                            | otherwise = False


-- b)

mejorNota :: [(String, Int, Int, Int)] -> [(String, Int)]
mejorNota [] = []
mejorNota ((nom, x, y, z):xs) = (nom, max x (max y z)): mejorNota xs


-- c)

incPrim :: [(Int, Int)] -> [(Int, Int)]
incPrim [] = []
incPrim ((x,y):xs) = (x+1,y): incPrim xs


-- d)

expandir :: String -> String
expandir "" = ""
expandir (x:xs) = x : " " ++ expandir xs


-- 21)

-- a)

verTodas :: [(String, Int, Int, String)] -> Int
verTodas [] = 0
verTodas ((n,a,l,d):xs) = l + verTodas xs

-- b)

estrenos :: [(String, Int, Int, String)] -> [String]
estrenos [] = []
estrenos ((n,a,l,d):xs) | a == 2016 = n: estrenos xs
                        | a /= 2016 = estrenos xs

-- c)

filmografia :: [(String, Int, Int, String)] -> String -> [String]
filmografia [] i = []
filmografia ((n,a,l,d):xs) i | d == i = n: filmografia xs i
                             | d /= i = filmografia xs i

-- d)

duracion :: [(String, Int, Int, String)] -> String -> Int
duracion [] i = 0
duracion ((n,a,l,d):xs) i | i == n = l
                          | i /= n = duracion xs i



-- 22)

vendedores :: [String] -> [String]
vendedores [] = []
vendedores (x:xs) = x:xs

ventas :: [((Int, Int, Int), String, [String])] -> [((Int, Int, Int), String, [String])]
ventas [] = []
ventas (x:xs) = x:xs

precios :: [(String, Int)] -> [(String, Int)]
precios [] = []
precios ((x,y):xs) = (x,y):xs

-- vendedores = ["Martin", "Diego", "Claudio", "José"]
-- ventas = [((1,2,2006), "Martin", ["Monitor GPRS 3000", "Motherboard ASUS 1500"]),((1,2,2006), "Diego", ["Monitor ASC 543", "Motherboard Pindorcho"]),((10,2,2006), "Martin", ["Monitor ASC 543", "Motherboard ASUS 1200"]),((12,2,2006), "Diego", ["Monitor GPRS 3000", "Motherboard ASUS 1200"]),((4,3,2006), "Diego", ["Monitor GPRS 3000", "Motherboard ASUS 1500"])]
-- precios = [("Monitor GPRS 3000", 200), ("Motherboard ASUS 1500", 120), ("Monitor ASC 543", 250),("Motherboard ASUS 1200", 100), ("Motherboard Pindorcho", 30)]


-- a)

precioMaquina :: [(String, Int)] -> [String] -> Int
precioMaquina n [] = 0
precioMaquina ((x,y):xs) (z:zs) | x == z = y + precioMaquina xs zs
                                | otherwise = precioMaquina xs zs


-- b)

cantVentasComponente :: [((Int, Int, Int), String, [String])] -> String -> Int
cantVentasComponente [] y = 0
cantVentasComponente (((n,n1,n2), n3, [x]):xs) y | x == y = length xs
                                                 | x /= y = cantVentasComponente xs y


aaa :: [[String]] -> String -> [String]
aaa [] y = []
aaa ([x]:xs) y | x == y = []:x: aaa xs y
               | x /= y = aaa xs y