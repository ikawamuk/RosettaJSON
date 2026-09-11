module RosettaJSON.Parse.ParseJSONString (parseJSONString) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseError (ParseError(..))

parseJSONString :: String -> Either ParseError (String, JSONValue)
parseJSONString ('"' : rest) = case go rest of
    Right (remaining, str) -> Right (remaining, JSONString str)
    Left err               -> Left err
parseJSONString _ = Left InvalidToken

go :: String -> Either ParseError (String, String)
go "" = Left InvalidToken
go ('"' : xs) = Right (xs, "")
go ('\\' : '"'  : xs) = attach '"'  (go xs)
go ('\\' : '\\' : xs) = attach '\\' (go xs)
go ('\\' : '/'  : xs) = attach '/'  (go xs)
go ('\\' : 'b'  : xs) = attach '\b' (go xs)
go ('\\' : 'f'  : xs) = attach '\f' (go xs)
go ('\\' : 'n'  : xs) = attach '\n' (go xs)
go ('\\' : 'r'  : xs) = attach '\r' (go xs)
go ('\\' : 't'  : xs) = attach '\t' (go xs)
go ('\\' : 'u' : a : b : c : d : xs)
    | all isHexDigit [a, b, c, d] =
        case hexToChar [a, b, c, d] of
            Just ch -> attach ch (go xs)
            Nothing -> Left InvalidToken
    | otherwise = Left InvalidToken
go (x : xs)
    | '\x20' <= x = attach x (go xs)
    | otherwise   = Left InvalidToken

attach :: Char -> Either ParseError (String, String) -> Either ParseError (String, String)
attach c (Right (rest, parsed)) = Right (rest, c : parsed)
attach _ (Left err)            = Left err

isHexDigit :: Char -> Bool
isHexDigit x = x `elem` "0123456789abcdefABCDEF"

hexVal :: Char -> Int
hexVal c
    | c >= '0' && c <= '9' = fromEnum c - fromEnum '0'
    | c >= 'a' && c <= 'f' = fromEnum c - fromEnum 'a' + 10
    | c >= 'A' && c <= 'F' = fromEnum c - fromEnum 'A' + 10
    | otherwise            = 0

hexToChar :: String -> Maybe Char
hexToChar str =
    let code = foldl (\acc ch -> acc * 16 + hexVal ch) 0 str
    in Just (toEnum code)
