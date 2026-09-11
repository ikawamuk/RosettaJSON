module RosettaJSON.Parse.ParseJSONLiteral
    ( parseJSONNull
    , parseJSONBool
    ) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseError (ParseError(..))

parseJSONNull :: String -> Either ParseError (String, JSONValue)
parseJSONNull s
    | take 4 s == "null" = Right (drop 4 s, JSONNull)
    | otherwise   = Left InvalidToken

parseJSONBool :: String -> Either ParseError (String, JSONValue)
parseJSONBool s
    | take 4 s == "true"  = Right (drop 4 s, JSONBool True)
    | take 5 s == "false" = Right (drop 5 s, JSONBool False)
    | otherwise   = Left InvalidToken
