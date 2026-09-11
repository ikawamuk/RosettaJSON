module RosettaJSON.Parse.ParseJSONNumber
    (parseJSONNumber) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseResult (ParseError(..), ParseResult)

parseJSONNumber :: String -> ParseResult
parseJSONNumber s = 
    case reads s of
        [(n, rest)] -> Right (rest, JSONNumber n)
        _           -> Left InvalidToken
