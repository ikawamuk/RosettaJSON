module RosettaJSON.Parse.ParseJSONNumber
    (parseJSONNumber) where

import RosettaJSON.Types (JSONValue(..))
import RosettaJSON.Parse.ParseError (ParseError(..))


parseJSONNumber :: String -> Either ParseError (String, JSONValue)
parseJSONNumber s = 
    case reads s of
        [(n, rest)] -> Right (rest, JSONNumber n)
        _           -> Left InvalidToken
