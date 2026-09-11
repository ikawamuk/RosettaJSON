module RosettaJSON.Parse.ParseJSONObject (parseJSONObject) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseResult (ParseError(..), ParseResult)

parseJSONObject :: (String -> ParseResult) -> (String -> ParseResult) -> String -> ParseResult 
parseJSONObject key_parser value_parser ('{' : rest) = case parseMembers key_parser value_parser (skipSpace rest) of
    Right (remaining, member) -> Right (remaining, JSONObject member)
    Left err                   -> Left err
parseJSONObject _ _ _ = Left InvalidToken

parseMembers :: (String -> ParseResult) -> (String -> ParseResult) -> String
                -> Either ParseError (String, [(String, JSONValue)])
parseMembers _ _ "" = Left InvalidToken
parseMembers _ _ ('}' : rest) = Right (rest, [])
parseMembers key_parser value_parser input = case key_parser input of
    Left err -> Left err
    Right (rest1, JSONString key) -> case skipSpace rest1 of
        (':' : rest2) -> case value_parser (skipSpace rest2) of
            Right (rest3, val) -> case skipSpace rest3 of
                ('}' : rest4) -> Right (rest4, [(key, val)])
                (',' : rest4) -> case parseMembers key_parser value_parser (skipSpace rest4) of
                    Right (rest5, members) -> Right (rest5, insertMember key val members)
                    Left err               -> Left err
                _ -> Left InvalidToken 
            Left err           -> Left err
        _ -> Left InvalidToken
    Right _ -> Left InvalidToken

insertMember :: String -> JSONValue -> [(String, JSONValue)] -> [(String, JSONValue)]
insertMember k v members
    | any (\(k', _) -> k == k') members = members
    | otherwise                         = (k, v) : members

skipSpace :: String -> String
skipSpace "" = ""
skipSpace (x : xs)
    | x `elem` " \t\r\n" = skipSpace xs
    | otherwise          = x : xs
