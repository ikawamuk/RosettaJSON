module RosettaJSON.Parse.ParseJSONString (parseJSONString) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseResult (ParseError(..), ParseResult)

parseJSONString :: String -> ParseResult
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
attach _ (Left err)             = Left err

isHexDigit :: Char -> Bool
isHexDigit x = x `elem` "0123456789abcdefABCDEF"

hexToChar :: String -> Maybe Char
hexToChar str
    | length str /= 4 = Nothing
    | otherwise       = toEnum <$> foldl accum (Just 0) str
  where
    accum Nothing _  = Nothing
    accum (Just acc) ch = case hexVal ch of
        Just v  -> Just (acc * 16 + v)
        Nothing -> Nothing

hexVal :: Char -> Maybe Int
hexVal c
    | c >= '0' && c <= '9' = Just (fromEnum c - fromEnum '0')
    | c >= 'a' && c <= 'f' = Just (fromEnum c - fromEnum 'a' + 10)
    | c >= 'A' && c <= 'F' = Just (fromEnum c - fromEnum 'A' + 10)
    | otherwise            = Nothing
