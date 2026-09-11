module RosettaJSON.Parse.ParseJSONLiteral
    ( parseJSONNull
    , parseJSONBool
    ) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseResult (ParseError(..), ParseResult)

parseJSONNull :: String -> ParseResult
parseJSONNull s
    | take 4 s == "null" = Right (drop 4 s, JSONNull)
    | otherwise   = Left InvalidToken

parseJSONBool :: String -> ParseResult
parseJSONBool s
    | take 4 s == "true"  = Right (drop 4 s, JSONBool True)
    | take 5 s == "false" = Right (drop 5 s, JSONBool False)
    | otherwise   = Left InvalidToken
