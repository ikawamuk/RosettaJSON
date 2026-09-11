module RosettaJSON.Parse.ParseJSONArray (parseJSONArray) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseResult (ParseError(..), ParseResult)

parseJSONArray :: (String -> ParseResult) -> String -> ParseResult 
parseJSONArray parser ('[' : rest) = case parseElements parser (skipSpace rest) of
    Right (remaining, elements) -> Right (remaining, JSONArray elements)
    Left err                   -> Left err
parseJSONArray _ _ = Left InvalidToken

parseElements :: (String -> ParseResult) -> String -> Either ParseError (String, [JSONValue])
parseElements _ "" = Left InvalidToken
parseElements _ (']' : rest) = Right (rest, [])
parseElements parser input = case parser input of
    Left err -> Left err
    Right (rest1, val) -> case skipSpace rest1 of
        (']' : rest2) -> Right (rest2, [val])
        (',' : rest2) -> case parseElements parser (skipSpace rest2) of
            Right (rest3, vals) -> Right (rest3, val : vals)
            Left err               -> Left err
        _ -> Left InvalidToken

skipSpace :: String -> String
skipSpace "" = ""
skipSpace (x : xs)
    | x `elem` " \t\r\n" = skipSpace xs
    | otherwise          = x : xs


