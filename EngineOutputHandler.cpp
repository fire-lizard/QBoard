#include "EngineOutputHandler.h"

void EngineOutputHandler::RemoveMove(std::vector<std::pair<int, int>>& moves, int x, int y)
{
	const long long cnt = static_cast<long long>(moves.size()) - 1;
	for (long long index = cnt; index >= 0; index--)
	{
		if (moves[index].first == x && moves[index].second == y)
			moves.erase(moves.begin() + index);
	}
}

bool EngineOutputHandler::IsLionMove(const std::optional<Piece>& piece, int x1, int y1, int x2, int y2)
{
	if (piece != std::nullopt)
	{
        if (piece->Type == Falcon)
		{
            if ((x1 == x2 && y1 - y2 == +1 || x1 == x2 && y1 - y2 == +2) && piece->Colour == White ||
                (x1 == x2 && y1 - y2 == -1 || x1 == x2 && y1 - y2 == -2) && piece->Colour == Black)
			{
				return true;
			}
		}
        else if (piece->Type == Eagle)
		{
            if ((abs(x1 - x2) == 1 && y1 - y2 == +1 || abs(x1 - x2) == 2 && y1 - y2 == +2) && piece->Colour == White ||
                (abs(x1 - x2) == 1 && y1 - y2 == -1 || abs(x1 - x2) == 2 && y1 - y2 == -2) && piece->Colour == Black)
			{
				return true;
			}
		}
        else if (piece->Type == FreeEagle || piece->Type == WingedTiger)
		{
			if (abs(x1 - x2) == 1 && abs(y1 - y2) == 1 || abs(x1 - x2) == 2 && abs(y1 - y2) == 2 ||
				abs(x1 - x2) == 2 && abs(y1 - y2) == 0 || abs(x1 - x2) == 0 && abs(y1 - y2) == 2)
			{
				return true;
			}
		}
        else if (piece->Type == GreatElephant)
		{
            if (piece->Colour == White && !(abs(x1 - x2) == 1 && y1 - y2 == +1 || abs(x1 - x2) == 2 && y1 - y2 == +2) ||
                piece->Colour == Black && !(abs(x1 - x2) == 1 && y1 - y2 == -1 || abs(x1 - x2) == 2 && y1 - y2 == -2))
			{
				return abs(x1 - x2) < 4 && abs(y1 - y2) < 4;
			}
		}
        else if (piece->Type == Lion || piece->Type == LionDog || piece->Type == FuriousFiend || piece->Type == Thunderclap ||
            piece->Type == KnightCaptain || piece->Type == ExtensiveFog || piece->Type == HolyLight ||
            piece->Type == WingedHorse || piece->Type == DoubleKylin || piece->Type == DoublePhoenix ||
            piece->Type == RoamingAssault)
		{
			return true;
		}
        else if (piece->Type == LionHawk || piece->Type == BuddhistSpirit || piece->Type == RisingDragon)
		{
			return abs(x1 - x2) < 3 && abs(y1 - y2) < 3;
		}
        else if (piece->Type == TeachingKing)
		{
			return abs(x1 - x2) < 4 && abs(y1 - y2) < 4;
		}
        else if (piece->Type == FlyingHawk)
		{
			return abs(x1 - x2) + abs(y1 - y2) < 3;
		}
	}
	return false;
}

void EngineOutputHandler::CalculateCheck(Board* board, PieceColour pieceColour, std::vector<std::pair<int, int>>& moves, int oldX, int oldY, int newX, int newY)
{
	Board* brd = board->Clone();
	brd->GetMoves(board->GetData(oldX, oldY), oldX, oldY);
	brd->Move(oldX, oldY, newX, newY);
    const auto location = brd->GetPieceLocation(King, pieceColour);
	const int kx = location.first;
	const int ky = location.second;
	auto opponentMoves = brd->GetAllMoves(pieceColour == White ? Black : White);
	std::ranges::for_each(opponentMoves, [&](const std::tuple<int, int, int, int>& t)
	{
		if (std::get<2>(t) == kx && std::get<3>(t) == ky)
		{
			board->RemoveMove(newX, newY);
			RemoveMove(moves, newX, newY);
		}
	});
	delete brd;
}

void EngineOutputHandler::CalculateXiangqiCheck(Board* board, std::vector<std::pair<int, int>>& moves, int oldX, int oldY, int newX, int newY)
{
    Board* brd = board->Clone();
    brd->GetMoves(board->GetData(oldX, oldY), oldX, oldY);
    brd->Move(oldX, oldY, newX, newY);
    if (dynamic_cast<XiangqiBoard*>(brd)->AreTwoKingsLookingOnEachOther())
    {
        board->RemoveMove(newX, newY);
        RemoveMove(moves, newX, newY);
    }
    delete brd;
}

QString EngineOutputHandler::TrySetFenToBoard(Board* board, const QByteArray& str, GameVariant gameVariant)
{
    Board* trial = board->Clone();
    const QString err = SetFenToBoard(trial, str, gameVariant);
    delete trial;
    if (err.isEmpty()) SetFenToBoard(board, str, gameVariant);
    return err;
}

void EngineOutputHandler::RollbackIllegalMove(GameVariant gameVariant, Board *board, std::vector<BoardSnapshot>& history)
{
    if (history.size() > 1)
    {
        history.pop_back();
        TrySetFenToBoard(board, QByteArray::fromStdString(history.back().fen), gameVariant);
        if (PieceStorage* ps = dynamic_cast<PieceStorage*>(board)) ps->SetCapturedPieces(history.back().pieces);
    }
}

std::vector<std::pair<int, int>> EngineOutputHandler::GetPieceLocations(const Board* board, PieceType pieceType, PieceColour pieceColour)
{
	int kx = -1, ky = -1;
	std::vector<std::pair<int, int>> result;
	for (int i = 0; i < board->GetWidth(); i++)
	{
		for (int j = 0; j < board->GetHeight(); j++)
		{
			const std::optional<Piece> p = board->GetData(i, j);
            if (p != std::nullopt && p->BaseType == pieceType && p->Colour == pieceColour)
			{
				kx = i;
				ky = j;
				result.emplace_back(kx, ky);
			}
		}
	}
	return result;
}

QByteArray EngineOutputHandler::ExtractMove(const QByteArray& buf, EngineProtocol engineProtocol, GameVariant gameVariant)
{
    // Handling Castling
	if (engineProtocol == XBoard && std::ranges::find(chessVariants, gameVariant) != std::end(chessVariants))
    {
        QStringList parts = QString(buf).trimmed().split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);
        if (std::ranges::any_of(parts, [](const QString& str) {return str == "move O-O-O";}))
            return "O-O-O";
        if (std::ranges::any_of(parts, [](const QString& str) {return str == "move O-O";}))
            return "O-O";
    }
    QByteArray result;
    if (engineProtocol == USI)
    {
    	static const QString _usre = R"(^bestmove ([RBGSNLP1-9])(\*|[a-i])([1-9])([a-i])(\+)?)";
        QRegularExpression regexp = QRegularExpression(_usre, QRegularExpression::MultilineOption);
    	QRegularExpressionMatch match = regexp.match(buf);
        if (match.hasMatch())
        {
            QString firstDigit = match.captured(1);
            QString firstLetter = match.captured(2);
            QString secondDigit = match.captured(3);
            QString secondLetter = match.captured(4);
            QString promotionChar = match.captured(5);
            result.push_back(firstDigit[0].toLatin1());
            result.push_back(firstLetter[0].toLatin1());
            result.push_back(secondDigit[0].toLatin1());
            result.push_back(secondLetter[0].toLatin1());
            if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
        }
    }
    else if (engineProtocol == UCI || engineProtocol == UCCI)
    {
        static const QString _ucre = R"(^bestmove ([a-i])([0-9])([a-i])([0-9])([nbrq])?)";
        QRegularExpression regexp = QRegularExpression(_ucre, QRegularExpression::MultilineOption);
        QRegularExpressionMatch match = regexp.match(buf);
        if (match.hasMatch())
        {
            QString firstLetter = match.captured(1);
            QString firstDigit = match.captured(2);
            QString secondLetter = match.captured(3);
            QString secondDigit = match.captured(4);
            QString promotionChar = match.captured(5);
            result.push_back(firstLetter[0].toLatin1());
            result.push_back(firstDigit[0].toLatin1());
            result.push_back(secondLetter[0].toLatin1());
            result.push_back(secondDigit[0].toLatin1());
            if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
        }
    }
    else if (engineProtocol == Qianhong)
    {
        static const QString _qhre = R"(([A-I])([0-9])(\-)([A-I])([0-9]))";
        QRegularExpression regexp = QRegularExpression(_qhre, QRegularExpression::MultilineOption);
        QRegularExpressionMatch match = regexp.match(buf);
        if (match.hasMatch())
        {
            QString firstLetter = match.captured(1);
            QString firstDigit = match.captured(2);
            QString secondLetter = match.captured(4);
            QString secondDigit = match.captured(5);
            result.push_back(firstLetter[0].toLatin1());
            result.push_back(static_cast<signed char>(firstDigit.toInt()));
            result.push_back(secondLetter[0].toLatin1());
            result.push_back(static_cast<signed char>(secondDigit.toInt()));
        }
    }
    else if (gameVariant == CapablancaChess ||
			 gameVariant == GothicChess || gameVariant == JanusChess || gameVariant == GrandChess ||
			 gameVariant == OmegaChess || gameVariant == CourierChess || gameVariant == GrandeAcedrex ||
			 gameVariant == FalconChess)
    {
        static const QString _bbre = R"(^move ([a-s])(1[0-6]|[0-9])([a-s])(1[0-6]|[0-9])([nbrqfjacwmM])?)";
        QRegularExpression regexp = QRegularExpression(_bbre, QRegularExpression::MultilineOption);
        QRegularExpressionMatch match = regexp.match(buf);
        if (match.hasMatch())
        {
            QString firstLetter = match.captured(1);
            QString firstDigit = match.captured(2);
            QString secondLetter = match.captured(3);
            QString secondDigit = match.captured(4);
            QString promotionChar = match.captured(5);
            result.push_back(firstLetter[0].toLatin1());
            result.push_back(static_cast<signed char>(firstDigit.toInt()));
            result.push_back(secondLetter[0].toLatin1());
            result.push_back(static_cast<signed char>(secondDigit.toInt()));
            if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
        }
    }
    else if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == TenjikuShogi || gameVariant == HeianDaiShogi ||
			 gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi || gameVariant == TaiShogi)
    {
        // Handling Null Move
        QStringList parts = QString(buf).trimmed().split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);
        if (std::ranges::any_of(parts, [](const QString& str) {return str == "move @@@@";}))
        {
            result = "@@@@";
        }
        else if (gameVariant == KoShogi)
        {
            // One token per move line: step "e6f6[+]", double "f6f7,f7f8[+]" (mid square repeated),
            // shoot "e6xh6[xk6][+]" (shooter stays). Encoded as file chars + binary rank bytes,
            // keeping the 'x'/'+' markers and dropping the comma, so a double becomes the same
            // 8-byte from/mid/mid/to array the multi-leg apply path already handles.
            static const QString _ksre = R"(^move ([a-s]1?[0-9](?:(?:x[a-s]1?[0-9]){1,2}|[a-s]1?[0-9](?:,[a-s]1?[0-9][a-s]1?[0-9])?)\+?))";
            QRegularExpression regexp = QRegularExpression(_ksre, QRegularExpression::MultilineOption);
            QRegularExpressionMatch match = regexp.match(buf);
            if (match.hasMatch())
            {
                const QString token = match.captured(1);
                for (qsizetype i = 0; i < token.size(); i++)
                {
                    const char c = token[i].toLatin1();
                    if (c >= '0' && c <= '9')
                    {
                        int rank = c - '0';
                        if (i + 1 < token.size() && token[i + 1].isDigit())
                        {
                            rank = rank * 10 + (token[++i].toLatin1() - '0');
                        }
                        result.push_back(static_cast<signed char>(rank));
                    }
                    else if (c != ',')
                    {
                        result.push_back(c);
                    }
                }
            }
        }
        else
        {
            static const QString _csre = R"(^move ([a-y])(2[0-5]|1?[0-9])([a-y])(2[0-5]|1?[0-9])(\+)?)";
            QRegularExpression regexp = QRegularExpression(_csre, QRegularExpression::MultilineOption);
            QRegularExpressionMatchIterator it = regexp.globalMatch(buf);
            while (it.hasNext())
            {
                QRegularExpressionMatch match = it.next();
                QString firstLetter = match.captured(1);
                QString firstDigit = match.captured(2);
                QString secondLetter = match.captured(3);
                QString secondDigit = match.captured(4);
                QString promotionChar = match.captured(5);
                result.push_back(firstLetter[0].toLatin1());
                result.push_back(static_cast<signed char>(firstDigit.toInt()));
                result.push_back(secondLetter[0].toLatin1());
                result.push_back(static_cast<signed char>(secondDigit.toInt()));
                if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
            }
        }
        }
    else if (gameVariant == CrazyWa)
    {
        static const QString _cwre = R"(^move ([PXRFSEODUGWVCLMHa-k])(@|1[0-1]|[0-9])([a-k])(1[0-1]|[0-9])(\+)?)";
        QRegularExpression regexp = QRegularExpression(_cwre, QRegularExpression::MultilineOption);
        QRegularExpressionMatch match = regexp.match(buf);
        if (match.hasMatch())
        {
            QString firstLetter = match.captured(1);
            QString firstDigit = match.captured(2);
            QString secondLetter = match.captured(3);
            QString secondDigit = match.captured(4);
            QString promotionChar = match.captured(5);
            result.push_back(firstLetter[0].toLatin1());
            result.push_back(firstDigit == '@' ? firstDigit[0].toLatin1() : static_cast<signed char>(firstDigit.toInt()));
            result.push_back(secondLetter[0].toLatin1());
            result.push_back(static_cast<signed char>(secondDigit.toInt()));
            if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
        }
    }
    else
    {
        static const QString _mcre = R"(^move ([a-h])([1-8])([a-h])([1-8])([nbrqlcudmaehfs])?)";
        static const QString _stre = R"(^move ([RNSFKa-h])(\@|[1-8])([a-h])([1-8])(f)?)";
        static const QString _sgre = R"(^move ([RBGSNLPFCWKHDYa-i])(@|[1-9])([a-i])([1-9])(\+)?)";
        static const QString _xbre = R"(^move ([a-i])([0-9])([a-i])([0-9])([+nbrqfjacwmM])?)";
        static const QString _chre = R"(^move ([PNBRQa-h])(@|[1-8])([a-h])([1-8])([nbrq])?)";
        QRegularExpression regexp;
        if (gameVariant == Sittuyin)
        {
            regexp = QRegularExpression(_stre, QRegularExpression::MultilineOption);
        }
        else if (gameVariant == CrazyHouse)
        {
            regexp = QRegularExpression(_chre, QRegularExpression::MultilineOption);
        }
        else if (gameVariant == MusketeerChess || gameVariant == SeirawanChess)
        {
            regexp = QRegularExpression(_mcre, QRegularExpression::MultilineOption);
        }
        else if (gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == MiniShogi ||
				 gameVariant == JudkinShogi || gameVariant == WhaleShogi || gameVariant == ToriShogi ||
				 gameVariant == EuroShogi || gameVariant == YariShogi || gameVariant == HeianShogi)
        {
            regexp = QRegularExpression(_sgre, QRegularExpression::MultilineOption);
        }
    	else
        {
             regexp = QRegularExpression(_xbre, QRegularExpression::MultilineOption);
        }
        QRegularExpressionMatch match = regexp.match(buf);
        if (match.hasMatch())
        {
            QString firstLetter = match.captured(1);
            QString firstDigit = match.captured(2);
            QString secondLetter = match.captured(3);
            QString secondDigit = match.captured(4);
            QString promotionChar = match.captured(5);
            result.push_back(firstLetter[0].toLatin1());
            result.push_back(firstDigit[0].toLatin1());
            result.push_back(secondLetter[0].toLatin1());
            result.push_back(secondDigit[0].toLatin1());
            if (!promotionChar.isEmpty()) result.push_back(promotionChar[0].toLatin1());
        }
    }
    return result;
}

Move EngineOutputHandler::ByteArrayToMove(QByteArray moveArray, EngineProtocol engineProtocol, int width, int height)
{
	int oldX, oldY, newX, newY;
	if (engineProtocol == Qianhong)
	{
        oldX = moveArray[0] - 65;
        oldY = height - moveArray[1];
        newX = moveArray[2] - 65;
        newY = height - moveArray[3];
	}
	else if (engineProtocol == USI)
	{
        oldX = width - moveArray[0] + 48;
        oldY = moveArray[1] - 97;
        newX = width - moveArray[2] + 48;
		newY = moveArray[3] - 97;
	}
    else if (width >= 10 || (width != 8 && width != 9 && height >= 10))
	{
        oldX = moveArray[0] - 97;
        oldY = height - moveArray[1];
        newX = moveArray[2] - 97;
        newY = height - moveArray[3];
	}
    else
	{
        oldX = moveArray[0] - 97;
        oldY = height - moveArray[1] + 48;
        newX = moveArray[2] - 97;
		newY = height - moveArray[3] + 48;
	}
	return {.x1 = oldX, .y1 = oldY, .x2 = newX, .y2 = newY};
}

QByteArray EngineOutputHandler::MoveToByteArray(Move m, EngineProtocol engineProtocol, int width, int height)
{
	QByteArray result;
	if (engineProtocol == USI)
	{
		result.append(width - m.x1);
		result.append(m.y1);
		result.append(width - m.x2);
		result.append(m.y2);
	}
	else
	{
		result.append(m.x1);
		result.append(height - m.y1);
		result.append(m.x2);
		result.append(height - m.y2);
	}
	return result;
}

// Rebuild the engine's own shoot token ("n3xq6", "e6xh6xk6", trailing '+') from the binary
// array ExtractMove produced. A shoot is not a from/to move - relaying it through
// ByteArrayToMove/MoveToByteArray reads the 'x' as a destination file and the victim's file
// byte as a rank, so "n3xq6" reaches the opponent engine as the unparseable "n3x11".
QByteArray EngineOutputHandler::KoShogiShootToText(const QByteArray& moveArray)
{
	QByteArray text;
	for (qsizetype i = 0; i < moveArray.size(); i++)
	{
		const char c = moveArray[i];
		if (c == 'x' || c == '+')
		{
			text.push_back(c);
			continue;
		}
		if (i + 1 >= moveArray.size()) break; // malformed: file char with no rank byte
		text.push_back(c);                                            // file a..s
		text += QByteArray::number(static_cast<int>(moveArray[++i])); // binary rank 1..19
	}
	return text;
}

// Where the king and the rook land when castling, given their files. Only the king's step differs
// between the variants - the rook always finishes on the square the king crossed - so the rule
// lives here once. It used to be copied into the click handler and into the engine-reply handler
// per variant, and the copies drifted: Janus put the king on i1 but told the engine h1, and
// Capablanca's queenside rook was written onto the square the king had just been placed on.
std::pair<int, int> EngineOutputHandler::CastlingTargets(GameVariant gameVariant, int kingX, int rookX)
{
    const bool kingside = rookX > kingX;
    int step = 2;
    if (gameVariant == CapablancaChess || gameVariant == GothicChess || gameVariant == FalconChess) step = 3;
    else if (gameVariant == JanusChess) step = kingside ? 4 : 3;
    const int kingTo = kingside ? kingX + step : kingX - step;
    return { kingTo, kingside ? kingTo - 1 : kingTo + 1 };
}

// The rank number as the engine counts it. Musketeer's gating rows and Grand/Xiangqi/Janggi's own
// numbering hold the back rank one row inside the array, so the plain height - y is off by one for
// them and the engine is handed a move on a rank the piece is not standing on.
int EngineOutputHandler::EngineRank(GameVariant gameVariant, int height, int y)
{
    return gameVariant == Xiangqi || gameVariant == Janggi || gameVariant == GrandChess ||
           gameVariant == MusketeerChess
        ? height - y - 1 : height - y;
}

// Hand the move the engine on turn just made to its opponent. The two colours had a copy each of
// this, and only the engine pointer differed. `castling` is what CastlingToMove read off the board
// before ReadStandardOutput moved the king, and is only looked at for an "O-O" reply. False means
// there was nothing to pass on - engine chatter, or a castling with no rook to castle with.
bool EngineOutputHandler::RelayMove(const std::shared_ptr<Engine>& to, const QByteArray& moveArray,
	const Move& castling, const Board* board, GameVariant gameVariant)
{
	if (moveArray.isEmpty()) return false;
	if (moveArray.contains("O-O"))
	{
		// "O-O" is the engine that sent it talking in its own notation, not a move the opponent has
		// to accept - a UCI opponent gets it spliced into its "position ... moves" list verbatim and
		// rejects the whole game. CECP spells castling as the king's own from-to.
		if (castling.x2 == -1) return false;
		const int rank = EngineRank(gameVariant, board->GetHeight(), castling.y1);
		to->Move(castling.x1, rank, CastlingTargets(gameVariant, castling.x1, castling.x2).first, rank, ' ');
	}
	else if (gameVariant == KoShogi && moveArray.contains('x'))
	{
		to->Move(KoShogiShootToText(moveArray));
	}
	else if (moveArray.size() < 8)
	{
		const Move m = ByteArrayToMove(moveArray, to->GetType(), board->GetWidth(), board->GetHeight());
		QByteArray convertedMoveArray = MoveToByteArray(m, to->GetType(), board->GetWidth(), board->GetHeight());
		to->Move(moveArray[1] == '*' || moveArray[1] == '@' ? moveArray[0] : convertedMoveArray[0],
		         moveArray[1] == '*' || moveArray[1] == '@' ? moveArray[1] : convertedMoveArray[1],
		         convertedMoveArray[2], convertedMoveArray[3], moveArray.size() > 4 ? moveArray[4] : ' ');
	}
	else if (moveArray.size() < 12)
	{
		std::dynamic_pointer_cast<WbEngine>(to)->DoubleMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3],
			moveArray[6], moveArray[7]);
	}
	else
	{
		std::dynamic_pointer_cast<WbEngine>(to)->TripleMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3],
			moveArray[6], moveArray[7], moveArray[10], moveArray[11]);
	}
	return true;
}

// "A king that moved more than one file has castled" was too generous: in Knightmate the royal
// piece is a knight, and every (2,1) jump it made matched. ApplyCastling then found a bishop where
// it wanted a rook and dropped the move without a word, so QBoard's board fell a move behind the
// engine's and everything after it came back "Illegal move". A castling stays on its rank and puts
// the king either on the square CastlingTargets names or - for engines that spell it king-takes-
// rook - on the rook itself. A knight's jump and a cylinder board's wrap-around match neither.
bool EngineOutputHandler::IsCastling(const QByteArray& moveArray, const Board* board, GameVariant gameVariant,
	int x1, int y1, int x2, int y2)
{
	if (moveArray.contains("O-O")) return true;
	const std::optional<Piece> king = board->GetData(x1, y1);
	if (y1 != y2 || abs(x1 - x2) <= 1 || king == std::nullopt || king->Type != King) return false;
	const std::optional<Piece> target = board->GetData(x2, y2);
	return x2 == CastlingTargets(gameVariant, x1, x2).first ||
	       (target != std::nullopt && target->Type == Rook && target->Colour == king->Colour);
}

// CECP lets an engine leave the piece letter off a promotion - "c7c8" rather than "c7c8q" - and a
// missing letter means a queen. Nebiyu always leaves it off. Without this the pawn stays a pawn on
// the last rank while the engine has a queen there, and the two boards drift apart from that move
// on. A move that did name its piece has already been promoted, so this sees no pawn and does
// nothing. Musketeer's gating rows and Omega's wizard rows hold the last rank one row inside the
// array, the same way EngineRank has to account for them.
void EngineOutputHandler::PromoteIfUnmarked(Board* board, GameVariant gameVariant, int x2, int y2)
{
	// Sittuyin promotes on a diagonal and usually in place ("d5d5f"), not by arriving anywhere, so
	// a pawn on its last rank there is still a pawn.
	if (gameVariant == Sittuyin) return;
	const std::optional<Piece> piece = board->GetData(x2, y2);
	if (piece == std::nullopt || piece->Type != Pawn) return;
	// How far inside the array the promotion row sits. Musketeer's gating rows and Omega's wizard
	// rows hold the last rank one row in; Makruk promotes on the sixth rank rather than the last.
	const int inset = gameVariant == Makruk ? 2
		: gameVariant == MusketeerChess || gameVariant == OmegaChess ? 1 : 0;
	if (y2 == (piece->Colour == White ? inset : board->GetHeight() - 1 - inset))
	{
		// One piece per variant, and every board that reaches here calls it a Queen: the Ferz of
		// Shatranj and Courier, the Met of Makruk, a real queen in Shatar and the chess variants.
		board->Promote(x2, y2, Queen);
	}
}

// "O-O" names no squares, so the from/to has to be read off the board: the king, and the rook it
// castles with. Spelling the squares out per variant instead got the rank wrong on every board
// whose back rank is not the edge row (Omega, Musketeer), used rank 10 for Black on the 8- and
// 9-rank boards, gave Janus Capablanca's king file, and handed ASCII digits to ByteArrayToMove
// where the wide boards encode the rank as a binary byte.
Move EngineOutputHandler::CastlingToMove(const QByteArray& c, const Board* board, PieceColour currentPlayer)
{
    const std::vector<std::pair<int, int>> kings = GetPieceLocations(board, King, currentPlayer);
    if (kings.empty()) return { .x1 = -1, .y1 = -1, .x2 = -1, .y2 = -1 };
    const auto [kingX, kingY] = kings.front();
    const std::pair<int, int> rook = board->FindNearestPiece(kingX, kingY, c == "O-O-O" ? West : East);
    return { .x1 = kingX, .y1 = kingY, .x2 = rook.first, .y2 = rook.second };
}

// x2 only says which side is being castled on: for an engine that spelled the move out it is the
// king's destination, for "O-O" it is the rook's square. The rook itself is found from the board.
// Returns the king's destination file, or -1 if there was no rook to castle with.
int EngineOutputHandler::ApplyCastling(Board* board, GameVariant gameVariant, int x1, int y1, int x2)
{
    if (x2 == -1) return -1;
    const std::pair<int, int> coords = board->FindNearestPiece(x1, y1, x1 < x2 ? East : West);
    if (coords.first == -1) return -1;
    const std::optional<Piece> king = board->GetData(x1, y1);
    if (king == std::nullopt) return -1;
    const std::optional<Piece> rook = board->GetData(coords.first, coords.second);
    // Engine output is not ours to trust: without this, a castling the engine should not have sent
    // relocates whatever piece happens to stand next to the king.
    if (rook == std::nullopt || rook->Type != Rook) return -1;
    const auto [kingTo, rookTo] = CastlingTargets(gameVariant, x1, coords.first);
    // Clear both origins first: a queenside king and rook can otherwise land on a square the
    // other one is still being written to, and the second write wins.
    board->SetData(x1, y1, std::nullopt);
    board->SetData(coords.first, coords.second, std::nullopt);
    board->SetData(kingTo, y1, king);
    board->SetData(rookTo, y1, rook);
    dynamic_cast<ChessBoard*>(board)->WriteCastling(kingTo > x1 ? "O-O" : "O-O-O", king->Colour);
    return kingTo;
}

void EngineOutputHandler::ReadStandardOutput(const QByteArray& buf, const std::shared_ptr<Engine>& engine, Board * board, QTextEdit * textEdit,
	GameVariant gameVariant, EngineOutput engineOutput, PieceColour currentPlayer)
{
	if (engine->GetType() == XBoard)
	{
		if (buf.contains("setboard=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("setboard", false);
		if (buf.contains("setboard=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("setboard", true);
		if (buf.contains("memory=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("memory", false);
		if (buf.contains("memory=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("memory", true);
		if (buf.contains("usermove=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("usermove", false);
		if (buf.contains("usermove=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("usermove", true);
	}
	const QByteArray moveArray = ExtractMove(buf, engine->GetType(), gameVariant);
    if (std::ranges::any_of(buf, [=](char t) {return isprint(t);}))
    {
        textEdit->setText(engineOutput == Verbose ? buf : moveArray);
    }
	if (moveArray.isEmpty()) return;
    const Move m = moveArray.contains("O-O") ?
        CastlingToMove(moveArray, board, currentPlayer) :
        ByteArrayToMove(moveArray, engine->GetType(), board->GetWidth(), board->GetHeight());
	int x1 = m.x1;
	int y1 = m.y1;
	int x2 = m.x2;
	int y2 = m.y2;
    const long long ms = moveArray.size();
    if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == TenjikuShogi || gameVariant == HeianDaiShogi ||
		gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi || gameVariant == TaiShogi)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
            if (gameVariant == KoShogi && moveArray.contains('x'))
            {
                // shoot capture: the shooter stays on (x1,y1); each "xFR" token names a removed victim
                for (long long i = 2; i + 2 < ms && moveArray[i] == 'x'; i += 3)
                {
                    const int vx = moveArray[i + 1] - 97;
                    const int vy = board->GetHeight() - moveArray[i + 2];
                    if (board->CheckPosition(vx, vy))
                    {
                        board->SetData(vx, vy, std::nullopt);
                    }
                }
                if (moveArray[ms - 1] == '+')
                {
                    board->Promote(x1, y1); // stationary in-zone promotion
                }
                return; // shoot not recorded in the engine's _moves transcript (write-only list, no shoot overload)
            }
            if (ms < 8)
			{
                const bool isPromoted = moveArray[ms - 1] == '+';
				board->GetMoves(board->GetData(x1, y1), x1, y1);
				const PieceType movedType = PieceTypeAt(board, x1, y1);
				board->Move(x1, y1, x2, y2, false);
                AddMove(board, gameVariant, movedType, x1, y1, x2, y2, isPromoted ? moveArray[ms - 1] : ' ', ' ');
                engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
				if (isPromoted)
				{
                    board->Promote(x2, y2);
				}
			}
			else
			{
				// Multi-leg: per-leg from/to pairs with mids repeated, so a double is
				// [A B B C] and a triple [A B B C C D]. Clear the captured mid squares
				// before relocating, since the final square may BE a mid (A->B->C->B).
				const bool triple = ms >= 12;
				const int x3 = moveArray[6] - 97;
				const int y3 = board->GetHeight() - moveArray[7];
				const int x4 = triple ? moveArray[10] - 97 : x3;
				const int y4 = triple ? board->GetHeight() - moveArray[11] : y3;
				const PieceType movedType = PieceTypeAt(board, x1, y1);
				board->SetData(x2, y2, std::nullopt);
				if (triple)
				{
					board->SetData(x3, y3, std::nullopt);
				}
				if (x1 != x4 || y1 != y4)
				{
					board->GetMoves(board->GetData(x1, y1), x1, y1);
					board->Move(x1, y1, x4, y4, false); // as above: the variant's own Move, so it burns
				}
                AddMove(board, gameVariant, movedType, x1, y1, x2, y2, x4, y4);
				if (triple)
				{
					std::dynamic_pointer_cast<WbEngine>(engine)->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, x3, board->GetHeight() - y3, x4, board->GetHeight() - y4);
				}
				else
				{
					std::dynamic_pointer_cast<WbEngine>(engine)->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, x4, board->GetHeight() - y4);
				}
				if (moveArray[ms - 1] == '+')
				{
					board->Promote(x4, y4);
				}
			}
		}
	}
    else if (gameVariant == Xiangqi || gameVariant == Janggi)
	{
		y1--;
		y2--;
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType movedType = PieceTypeAt(board, x1, y1);
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2, ' ', ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
	}
    else if (gameVariant == GrandChess)
    {
        y1--;
        y2--;
        if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
        {
            const bool isPromoted =
                moveArray[ms - 1] == 'n' || moveArray[ms - 1] == 'b' || moveArray[ms - 1] == 'r' ||
                moveArray[ms - 1] == 'q' || moveArray[ms - 1] == 'a' || moveArray[ms - 1] == 'c';
            board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType movedType = PieceTypeAt(board, x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
            board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2,
                    isPromoted ? moveArray[ms - 1] : ' ', ct != None ? 'x' : ' ');
            engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
            if (isPromoted)
            {
                switch (moveArray[ms - 1])
                {
                case 'n':
                    board->Promote(x2, y2, Knight);
                    break;
                case 'b':
                    board->Promote(x2, y2, Bishop);
                    break;
                case 'r':
                    board->Promote(x2, y2, Rook);
                    break;
                case 'q':
                    board->Promote(x2, y2, Queen);
                    break;
                case 'a':
                    board->Promote(x2, y2, Archbishop);
                    break;
                case 'c':
                    board->Promote(x2, y2, Chancellor);
                    break;
                default:
                    break;
                }
            }
        }
    }
    else if (gameVariant == OmegaChess)
    {
        // Castling check
        if (IsCastling(moveArray, board, gameVariant, x1, y1, x2, y2))
        {
            const int kingTo = ApplyCastling(board, gameVariant, x1, y1, x2);
            const int rank = EngineRank(gameVariant, board->GetHeight(), y1);
            if (kingTo != -1) engine->AddMove(x1, rank, kingTo, rank, ' ');
        }
        else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
        {
            const bool isPromoted =
                moveArray[ms - 1] == 'n' || moveArray[ms - 1] == 'b' || moveArray[ms - 1] == 'r' ||
                moveArray[ms - 1] == 'q' || moveArray[ms - 1] == 'c' || moveArray[ms - 1] == 'w';
            board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType movedType = PieceTypeAt(board, x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
            board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2,
                    isPromoted ? moveArray[ms - 1] : ' ', ct != None ? 'x' : ' ');
            engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
            if (isPromoted)
            {
                switch (moveArray[ms - 1])
                {
                case 'n':
                    board->Promote(x2, y2, Knight);
                    break;
                case 'b':
                    board->Promote(x2, y2, Bishop);
                    break;
                case 'r':
                    board->Promote(x2, y2, Rook);
                    break;
                case 'q':
                    board->Promote(x2, y2, Queen);
                    break;
                case 'c':
                    board->Promote(x2, y2, Champion);
                    break;
                case 'w':
                    board->Promote(x2, y2, Wizard);
                    break;
                default:
                    break;
                }
            }
            PromoteIfUnmarked(board, gameVariant, x2, y2);
        }
    }
    else if (gameVariant == SeirawanChess)
    {
        SeirawanChessBoard* sb = dynamic_cast<SeirawanChessBoard*>(board);
        const PieceType gated = ms > 4 ? SeirawanCharPiece(moveArray[ms - 1]) : None;
        if (IsCastling(moveArray, board, gameVariant, x1, y1, x2, y2))
        {
            const int kingTo = ApplyCastling(board, gameVariant, x1, y1, x2);
            if (kingTo != -1)
            {
                // Both engines gate onto the king's own square when castling.
                if (gated != None && sb != nullptr) sb->Gate(x1, y1, gated, currentPlayer);
                const int rank = EngineRank(gameVariant, board->GetHeight(), y1);
                engine->AddMove(x1, rank, kingTo, rank, gated != None ? moveArray[ms - 1] : ' ');
            }
        }
        else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
        {
            const PieceType movedType = PieceTypeAt(board, x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
            board->GetMoves(board->GetData(x1, y1), x1, y1);
            board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2,
                gated != None ? moveArray[ms - 1] : ' ', ct != None ? 'x' : ' ');
            engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, gated != None ? moveArray[ms - 1] : ' ');
            if (gated != None)
            {
                if (movedType == Pawn)
                {
                    board->Promote(x2, y2, gated);
                }
                else if (sb != nullptr)
                {
                    sb->Gate(x1, y1, gated, currentPlayer);
                }
            }
            PromoteIfUnmarked(board, gameVariant, x2, y2);
        }
    }
    else if (gameVariant == MusketeerChess)
    {
        // The gating rows push the back rank one row in, which ByteArrayToMove knows nothing
        // about. CastlingToMove reads the king off the board, so its rows are already right.
        if (!moveArray.contains("O-O"))
        {
            y1--;
            y2--;
        }
        // Castling check
        if (IsCastling(moveArray, board, gameVariant, x1, y1, x2, y2))
        {
            const int kingTo = ApplyCastling(board, gameVariant, x1, y1, x2);
            const int rank = EngineRank(gameVariant, board->GetHeight(), y1);
            if (kingTo != -1) engine->AddMove(x1, rank, kingTo, rank, ' ');
        }
        else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
        {
            const bool isPromoted =
                moveArray[ms - 1] == 'n' || moveArray[ms - 1] == 'b' || moveArray[ms - 1] == 'r' ||
                moveArray[ms - 1] == 'q' || moveArray[ms - 1] == 'a' || moveArray[ms - 1] == 'm' ||
                moveArray[ms - 1] == 'l' || moveArray[ms - 1] == 'c' || moveArray[ms - 1] == 'u' ||
                moveArray[ms - 1] == 'd' || moveArray[ms - 1] == 'e' || moveArray[ms - 1] == 'h' ||
                moveArray[ms - 1] == 'f' || moveArray[ms - 1] == 's';
            board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType movedType = PieceTypeAt(board, x1, y1);
            const PieceType ct1 = board->GetData(x1, y1) != std::nullopt ? board->GetData(x1, y1)->Type : None;
            const PieceType ct2 = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
            board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2,
                isPromoted ? moveArray[ms - 1] : ' ', ct2 != None ? 'x' : ' ');
            engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
        	if (isPromoted)
            {
                PieceType pt;
                switch (moveArray[ms - 1])
                {
                case 'l':
                    pt = Leopard;
                    break;
                case 'c':
                    pt = Cannon;
                    break;
                case 'u':
                    pt = Unicorn;
                    break;
                case 'd':
                    pt = FlyingDragon;
                    break;
                case 'e':
                    pt = Elephant;
                    break;
                case 'h':
                    pt = Eagle;
                    break;
                case 'f':
                    pt = Fortress;
                    break;
                case 's':
                    pt = Spider;
                    break;
                case 'n':
                    pt = Knight;
                    break;
                case 'b':
                    pt = Bishop;
                    break;
                case 'r':
                    pt = Rook;
                    break;
                case 'q':
                    pt = Queen;
                    break;
                case 'a':
                    pt = Archbishop;
                    break;
                case 'm':
                    pt = Chancellor;
                    break;
                default:
                    pt = None;
                    break;
                }
                if (ct1 == Pawn && pt != None)
                {
                    board->Promote(x2, y2, pt);
                }
                else
                {
                    board->SetData(x1, y1, Piece(pt, currentPlayer));
                }
            }
            PromoteIfUnmarked(board, gameVariant, x2, y2);
        }
    }
    else if (std::ranges::find(chessVariants, gameVariant) != std::end(chessVariants))
	{
    	if (gameVariant == CrazyHouse && (moveArray[1] == '@' || moveArray[1] == '*'))
		{
            const PieceType dropped = StringManager::StringCode2PieceType(gameVariant, std::string(1, moveArray[0]));
            PieceStorage* cps = dynamic_cast<PieceStorage*>(board);
            if (dropped != None && board->CheckPosition(x2, y2) && board->GetData(x2, y2) == std::nullopt)
            {
                board->SetData(x2, y2, Piece(dropped, currentPlayer));
                if (cps != nullptr) cps->RemoveCapturedPiece(dropped, currentPlayer);
                AddMove(board, gameVariant, dropped, moveArray[0], moveArray[1], x2, y2, ' ', ' ');
                engine->AddMove(moveArray[0], moveArray[1], x2, board->GetHeight() - y2, ' ');
            }
		}
    	// Castling check
        else if (IsCastling(moveArray, board, gameVariant, x1, y1, x2, y2))
		{
            const int kingTo = ApplyCastling(board, gameVariant, x1, y1, x2);
            const int rank = EngineRank(gameVariant, board->GetHeight(), y1);
            if (kingTo != -1) engine->AddMove(x1, rank, kingTo, rank, ' ');
		}
		else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
            const bool isPromoted =
                moveArray[ms - 1] == 'n' || moveArray[ms - 1] == 'b' || moveArray[ms - 1] == 'r' ||
                moveArray[ms - 1] == 'q' || moveArray[ms - 1] == 'a' || moveArray[ms - 1] == 'c' ||
                moveArray[ms - 1] == 'f';
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType movedType = PieceTypeAt(board, x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2,
                    isPromoted ? moveArray[ms - 1] : ' ', ct != None ? 'x' : ' ');
            engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
			if (isPromoted)
			{
                switch (moveArray[ms - 1])
				{
                case 'n':
                    board->Promote(x2, y2, Knight);
                    break;
                case 'b':
                    board->Promote(x2, y2, Bishop);
                    break;
                case 'r':
                    board->Promote(x2, y2, Rook);
                    break;
                case 'q':
                    board->Promote(x2, y2, Queen);
                    break;
                case 'a':
                    board->Promote(x2, y2, Archbishop);
                    break;
                case 'c':
                    board->Promote(x2, y2, Chancellor);
                    break;
                case 'f':
                    board->Promote(x2, y2, Falcon);
                    break;
                default:
					break;
				}
			}
			PromoteIfUnmarked(board, gameVariant, x2, y2);
		}
	}
    else if (gameVariant == GrandeAcedrex)
    {
        if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
        {
            const bool isPromoted =
                moveArray[ms - 1] == 'u' || moveArray[ms - 1] == 'l' || moveArray[ms - 1] == 'r' ||
                moveArray[ms - 1] == 'g' || moveArray[ms - 1] == 'a' || moveArray[ms - 1] == 'c';
            board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType movedType = PieceTypeAt(board, x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
            board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2,
                    isPromoted ? moveArray[ms - 1] : ' ', ct != None ? 'x' : ' ');
            engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
            if (isPromoted)
            {
                switch (moveArray[ms - 1])
                {
                case 'u':
                    board->Promote(x2, y2, Unicorn);
                    break;
                case 'l':
                    board->Promote(x2, y2, Lion);
                    break;
                case 'r':
                    board->Promote(x2, y2, Rook);
                    break;
                case 'g':
                    board->Promote(x2, y2, Giraffe);
                    break;
                case 'a':
                    board->Promote(x2, y2, Aanca);
                    break;
                case 'c':
                    board->Promote(x2, y2, Bishop);
                    break;
                default:
                    break;
                }
            }
        }
    }
    else if (gameVariant == Shatranj || gameVariant == Shatar || gameVariant == Sittuyin || gameVariant == CourierChess)
	{
        if (gameVariant == Sittuyin && moveArray[1] == '@')
        {
            PieceType newPiece;
            switch (moveArray[0])
            {
            case 'K':
                newPiece = King;
                break;
            case 'F':
                newPiece = Queen;
                break;
            case 'S':
                newPiece = Bishop;
                break;
            case 'N':
                newPiece = Knight;
                break;
            case 'R':
                newPiece = Rook;
                break;
            default:
                newPiece = None;
                break;
            }
            board->SetData(x2, y2, Piece(newPiece, currentPlayer));
            AddMove(board, gameVariant, PieceTypeAt(board, x2, y2), moveArray[0], moveArray[1], x2, y2, ' ', ' ');
            engine->AddMove(moveArray[0], moveArray[1], x2, board->GetHeight() - y2, ' ');
        }
    	else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
    		const bool isPromoted = moveArray[ms - 1] == 'f' || moveArray[ms - 1] == 'j' || moveArray[ms - 1] == 'q';
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType movedType = PieceTypeAt(board, x1, y1);
			// Sittuyin promotes in place ("d5d5f"): the piece standing on the destination is the promoting pawn itself, not a victim.
            const PieceType ct = (x1 != x2 || y1 != y2) && board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2, isPromoted ? moveArray[ms - 1] : ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[ms - 1] : ' ');
			if (isPromoted)
			{
                board->Promote(x2, y2);
			}
			PromoteIfUnmarked(board, gameVariant, x2, y2);
		}
	}
	else if (gameVariant == Makruk)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
            const bool isPromoted = moveArray[ms - 1] == 'm' || moveArray[ms - 1] == 'M';
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType movedType = PieceTypeAt(board, x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, movedType, x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[ms - 1] : ' ');
			if (isPromoted)
			{
                board->Promote(x2, y2);
			}
			PromoteIfUnmarked(board, gameVariant, x2, y2);
		}
	}
    else if (gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi ||
             gameVariant == JudkinShogi || gameVariant == WhaleShogi || gameVariant == ToriShogi || gameVariant == EuroShogi || gameVariant == YariShogi ||
             gameVariant == HeianShogi || gameVariant == CrazyWa)
	{
        if ((gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi || gameVariant == WhaleShogi ||
             gameVariant == ToriShogi || gameVariant == EuroShogi || gameVariant == YariShogi || gameVariant == CrazyWa) && (moveArray[1] == '@' || moveArray[1] == '*'))
		{
			PieceType newPiece;
            if (gameVariant == WhaleShogi)
            {
                switch (moveArray[0])
                {
                case 'B':
                    newPiece = BlueWhale;
                    break;
                case 'N':
                    newPiece = Narwhal;
                    break;
                case 'K':
                    newPiece = DragonKing;
                    break;
                case 'G':
                    newPiece = GreyWhale;
                    break;
                case 'H':
                    newPiece = Humpback;
                    break;
                case 'D':
                    newPiece = Pawn;
                    break;
                default:
                    newPiece = None;
                    break;
                }
            }
            else if (gameVariant == ToriShogi)
            {
                switch (moveArray[0])
                {
                case 'F':
                    newPiece = Falcon;
                    break;
                case 'C':
                    newPiece = Crane;
                    break;
                case 'P':
                    newPiece = Pheasant;
                    break;
                case 'L':
                    newPiece = LeftQuail;
                    break;
                case 'R':
                    newPiece = RightQuail;
                    break;
                case 'S':
                    newPiece = Pawn;
                    break;
                default:
                    newPiece = None;
                    break;
                }
            }
            else if (gameVariant == YariShogi)
            {
                switch (moveArray[0])
                {
                case 'N':
                    newPiece = YariKnight;
                    break;
                case 'R':
                    newPiece = YariRook;
                    break;
                case 'B':
                    newPiece = YariBishop;
                    break;
                case 'P':
                    newPiece = Pawn;
                    break;
                default:
                    newPiece = None;
                    break;
                }
            }
            else if (gameVariant == CrazyWa)
			{
                switch (moveArray[0])
                {
                case 'D':
                    newPiece = Dog;
                    break;
                case 'R':
                    newPiece = RunningRabbit;
                    break;
                case 'W':
                    newPiece = Gold;
                    break;
                case 'V':
                    newPiece = Silver;
                    break;
                case 'X':
                    newPiece = TreacherousFox;
                    break;
                case 'M':
                    newPiece = ClimbingMonkey;
                    break;
                case 'G':
                    newPiece = FlyingGoose;
                    break;
                case 'C':
                    newPiece = FlyingCock;
                    break;
                case 'F':
                    newPiece = FlyingFalcon;
                    break;
                case 'U':
                    newPiece = StruttingCrow;
                    break;
                case 'E':
                    newPiece = CloudEagle;
                    break;
                case 'L':
                    newPiece = SwoopingOwl;
                    break;
                case 'H':
                    newPiece = LiberatedHorse;
                    break;
                case 'S':
                    newPiece = SideMover;
                    break;
                case 'O':
                    newPiece = Lance;
                    break;
                case 'P':
                    newPiece = Pawn;
                    break;
                default:
                    newPiece = None;
                    break;
                }
			}
			else
			{
                switch (moveArray[0])
                {
                case 'R':
                    newPiece = Rook;
                    break;
                case 'B':
                    newPiece = Bishop;
                    break;
                case 'G':
                    newPiece = Gold;
                    break;
                case 'S':
                    newPiece = Silver;
                    break;
                case 'N':
                    newPiece = Knight;
                    break;
                case 'L':
                    newPiece = Lance;
                    break;
                // Kyoto's tokin. Without it the drop landed a typeless, imageless piece on the
                // square and the board never matched the engine's again.
                case 'T':
                    newPiece = Tokin;
                    break;
                case 'P':
                    newPiece = Pawn;
                    break;
                default:
                    newPiece = None;
                    break;
                }
            }
            board->SetData(x2, y2, Piece(newPiece, currentPlayer));
            // The drop does not go through Board::Move, so nothing else takes the piece out of the
            // engine's hand - and the hand QBoard shows for it would only ever grow. A Kyoto coin is
            // held under whichever face it was captured on, which need not be the face dropped.
            if (auto* store = dynamic_cast<PieceStorage*>(board);
                store != nullptr && !store->RemoveCapturedPiece(newPiece, currentPlayer) && gameVariant == KyotoShogi)
            {
                store->RemoveCapturedPiece(KyotoFlip(newPiece), currentPlayer);
            }
            AddMove(board, gameVariant, PieceTypeAt(board, x2, y2), moveArray[0], moveArray[1], x2, y2, ' ', ' ');
            if (engine->GetType() == USI)
            {
                engine->AddMove(moveArray[0], moveArray[1], board->GetWidth() - x2, y2, ' ');
            }
            else
            {
                engine->AddMove(moveArray[0], moveArray[1], x2, board->GetHeight() - y2, ' ');
            }
		}
		else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
            const bool isPromoted = moveArray[ms - 1] == '+';
			board->GetMoves(board->GetData(x1, y1), x1, y1);
            auto destPiece = board->GetData(x2, y2);
			board->Move(x1, y1, x2, y2, false);
            if (board->GetData(x2, y2) != std::nullopt)
            {
                AddMove(board, gameVariant, board->GetData(x2, y2)->BaseType, x1, y1, x2, y2, isPromoted ? moveArray[ms - 1] : ' ', ' ');
            }
            if (engine->GetType() == USI)
            {
                engine->AddMove(board->GetWidth() - x1, y1, board->GetWidth() - x2, y2, isPromoted ? moveArray[ms - 1] : ' ');
            }
            else
            {
                engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
            }
			if (isPromoted || gameVariant == KyotoShogi || (gameVariant == MicroShogi && destPiece != std::nullopt))
			{
                board->Promote(x2, y2);
            }
        }
	}
}

int EngineOutputHandler::GetEnPassantRank(GameVariant gameVariant, PieceColour pieceColour, const char y)
{
	switch (gameVariant)
	{
    case ChancellorChess:
    case ModernChess:
        return pieceColour == Black ? 5 : 3;
    case GrandChess:
    case MusketeerChess:
        return pieceColour == Black ? 5 : 4;
	case OmegaChess:
        return y - 48 + ('6' - y) * 2;
    default:
        return pieceColour == Black ? 4 : 3;
	}
}

char EngineOutputHandler::ChessPieceChar(PieceType chessPiece)
{
    switch (chessPiece)
    {
    case Rook:
        return 'r';
    case Knight:
    case Nightrider:
        return 'n';
    case Bishop:
        return 'b';
    case Archbishop:
        return 'a';
    case Chancellor:
    case Champion:
        return 'c';
    case Falcon:
        return 'f';
    case Wizard:
        return 'w';
    default:
        return 'q';
    }
}

// Musketeer Chess needs its own letters: 'c' is the Cannon here, not the Chancellor that
// ChessPieceChar would give it. These are the letters the gating moves above are read back with.
char EngineOutputHandler::MusketeerPieceChar(PieceType musketeerPiece)
{
    switch (musketeerPiece)
    {
    case Leopard:      return 'l';
    case Cannon:       return 'c';
    case Unicorn:      return 'u';
    case FlyingDragon: return 'd';
    case Elephant:     return 'e';
    case Eagle:        return 'h';
    case Fortress:     return 'f';
    case Spider:       return 's';
    case Archbishop:   return 'a';
    case Chancellor:   return 'm';
    default:           return ' ';
    }
}

char EngineOutputHandler::SeirawanPieceChar(PieceType seirawanPiece)
{
    switch (seirawanPiece)
    {
    case Archbishop: return 'h';
    case Chancellor: return 'e';
    default:         return ChessPieceChar(seirawanPiece);
    }
}

PieceType EngineOutputHandler::SeirawanCharPiece(char letter)
{
    switch (letter)
    {
    case 'h': return Archbishop;
    case 'e': return Chancellor;
    case 'n': return Knight;
    case 'b': return Bishop;
    case 'r': return Rook;
    case 'q': return Queen;
    default:  return None;
    }
}

void EngineOutputHandler::ReadStandardError(const QByteArray& buf, QTextEdit* textEdit)
{
	textEdit->setHtml("<p style='color:red'>" + buf + "</p>");
}

PieceType EngineOutputHandler::PieceTypeAt(const Board* board, int x, int y)
{
	const std::optional<Piece> piece = board->CheckPosition(x, y) ? board->GetData(x, y) : std::nullopt;
	return piece != std::nullopt ? piece->Type : None;
}

void EngineOutputHandler::AddMove(Board* board, GameVariant gameVariant, PieceType p, int x1, int y1, int x2, int y2, int x3, int y3)
{
    if (gameVariant == MusketeerChess)
    {
    }
	else if (std::ranges::find(chessVariants, gameVariant) != std::end(chessVariants) ||
		gameVariant == Shatranj || gameVariant == Shatar || gameVariant == Sittuyin)
	{
		dynamic_cast<ShatranjBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Makruk)
	{
		dynamic_cast<MakrukBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
    else if (gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == ShoShogi ||
             gameVariant == MiniShogi || gameVariant == JudkinShogi || gameVariant == EuroShogi || gameVariant == CrazyWa)
	{
		dynamic_cast<ShogiBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Xiangqi)
	{
		dynamic_cast<XiangqiBoard*>(board)->WriteMove(p, x1, y1, x2, y2);
	}
}

template <typename T> std::basic_string<T> EngineOutputHandler::uppercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::toupper(v)); });
	return s2;
}

template <typename T> std::basic_string<T> EngineOutputHandler::lowercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::tolower(v)); });
	return s2;
}

// Variants whose FEN carries a holdings field as the third field. GetFenFromBoard writes it and
// SetFenToBoard reads it, so the two must agree or a position stops round-tripping. (Sittuyin and
// Musketeer Chess also have holdings, but theirs go in brackets after the placement.)
bool EngineOutputHandler::HasHoldingsField(GameVariant gameVariant)
{
	return gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == MiniShogi ||
		gameVariant == JudkinShogi || gameVariant == WhaleShogi || gameVariant == ToriShogi || gameVariant == EuroShogi ||
		gameVariant == YariShogi || gameVariant == CrazyWa || gameVariant == CrazyHouse;
}

// The inverse of SetFenToBoard. Board::GetFEN() is the piece placement alone, so anything that
// ships a bare GetFEN() loses the state that lives beside the squares -- castling rights, the en
// passant square, the pieces in hand -- and the receiver silently keeps its own stale copy.
QString EngineOutputHandler::GetFenFromBoard(Board* board, GameVariant gameVariant, PieceColour sideToMove)
{
	QString fen = QString::fromStdString(board->GetFEN());
	// Pieces in hand (or still to be placed) go in brackets straight after the placement, one letter
	// each, uppercase for White. That is what the engines read: the shogi variants used to write the
	// hand as a field of its own after the side to move, which every engine ignored, so a position
	// handed over with setboard arrived with the right pieces on the board and an empty hand.
	if (gameVariant == Sittuyin || gameVariant == MusketeerChess || gameVariant == SeirawanChess || HasHoldingsField(gameVariant))
	{
		const auto pieceCodes = StringManager::GetOrderData(gameVariant).first;
		auto* stb = dynamic_cast<PieceStorage*>(board);
		QString cpStr;
		if (stb != nullptr)
		{
			for (const auto& capturedPiece : stb->GetCapturedPieces(White))
			{
				const auto it = pieceCodes.find(capturedPiece);
				if (it != pieceCodes.end()) cpStr += QString::fromStdString(it->second);
			}
			for (const auto& capturedPiece : stb->GetCapturedPieces(Black))
			{
				const auto it = pieceCodes.find(capturedPiece);
				if (it != pieceCodes.end()) cpStr += static_cast<char>(std::tolower(it->second[0]));
			}
		}
		fen += "[" + cpStr + "]";
	}
	fen += sideToMove == Black ? " b" : " w";
	if (std::ranges::find(chessVariants, gameVariant) != std::end(chessVariants))
	{
		auto* cb = dynamic_cast<ChessBoard*>(board);
		auto* sb = dynamic_cast<SeirawanChessBoard*>(board);
		if (cb != nullptr)
		{
			fen += " " + (sb != nullptr ? QString::fromStdString(sb->GatingRights())
				: gameVariant != GrandChess ? QString::fromStdString(cb->GetCastling()) : "-");
			fen += " " + QString::fromStdString(cb->GetEnPassant());
			fen += " " + QString::number(cb->HalfMoveCount());
		}
	}
	else if (HasHoldingsField(gameVariant))
	{
		fen += " -"; // placeholder where the hand used to sit, so the move number keeps its field
	}
	fen += " " + QString::number(board->MoveCount());
	return fen;
}

QString EngineOutputHandler::SetFenToBoard(Board* board, const QByteArray& str, GameVariant gameVariant)
{
	QStringList parts;
	QString bracketed;
	const bool hasPieces = gameVariant == Sittuyin || gameVariant == MusketeerChess ||
		gameVariant == SeirawanChess || HasHoldingsField(gameVariant);
    if (hasPieces)
    {
        QString rest = QString(str).trimmed();
        const qsizetype open = rest.indexOf('[');
        const qsizetype close = rest.indexOf(']', open);
        if (open >= 0 && close > open)
        {
            bracketed = rest.mid(open + 1, close - open - 1);
            rest = rest.left(open) + rest.mid(close + 1);
        }
        parts = rest.split(' ', Qt::SkipEmptyParts);
    }
    else
    {
        parts = QString(str).trimmed().split(' ', Qt::SkipEmptyParts);
    }
	if (parts.isEmpty() || parts.first().isEmpty())
		return "Empty FEN string"; // guard before indexing parts[0]/fen[0]; also avoids wiping the board on junk input
	QString fen = parts[0];
	board->Clear();
	const int w = board->GetWidth();
	const int h = board->GetHeight();
	int i = 0, j = 0, k = 0;
    bool isDigit = false;
    std::string promo;
    do
	{
        const char c = fen[k].toLatin1();
		if (c == '/')
		{
            k++;
			j++;
			i = 0;
            isDigit = false;
        }
		else if (c == '+')
		{
			k++;
			promo = "+";
            isDigit = false;
        }
        else if (c >= '0' && c <= '9')
		{
			k++;
			i += c - 48;
            if (!isDigit)
            {
                isDigit = true;
            }
            else
            {
                const int step = fen[k - 2].toLatin1() - 48;
                i += step * 9;
                isDigit = false;
            }
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
            isDigit = false;
            std::string stringCode(1, c);
			PieceType pieceType;
            if (gameVariant == DaiShogi || gameVariant == TenjikuShogi || gameVariant == YariShogi ||
				gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi || gameVariant == TaiShogi)
			{
				if (k < fen.size() - 1 && (fen[k + 1] == '\'' || fen[k + 1] == '!' || fen[k + 1] == '~' || fen[k + 1] == '`'))
				{
					k++;
					stringCode.push_back(fen[k].toLatin1());
				}
			}
            pieceType = StringManager::StringCode2PieceType(gameVariant, uppercase(stringCode));
            if (pieceType == None)
			{
				return "Unknown character found in the FEN string at position " + QString::number(k);
			}
			if (j == h || i == w)
			{
				return "Incorrent FEN string length for this game";
			}
			board->SetData(i, j, std::make_optional<Piece>(pieceType, c >= 'a' && c <= 'z' ? Black : White));
            if (promo == "+" && gameVariant != MicroShogi && gameVariant != KyotoShogi)
            {
                board->Promote(i, j);
            }
            promo = "";
			k++;
			i++;
		}
        else
        {
            return "Invalid character found in the FEN string at position " + QString::number(k);
        }
	} while ((i < w || j < h - 1) && k < fen.size());
    if (std::ranges::find(chessVariants, gameVariant) != std::end(chessVariants))
	{
		ChessBoard* cb = dynamic_cast<ChessBoard*>(board);
		if (parts.size() >= 3)
		{
			cb->SetCastling(parts[2].toStdString());
		}
		if (parts.size() >= 4)
		{
			// the file letter runs to the board's own width -- Capablanca and Grand reach 'j'
			if (parts[3].size() == 2 && parts[3][0] >= 'a' && parts[3][0] < QChar('a' + board->GetWidth()) &&
				parts[3][1] >= '1' && parts[3][1] <= '8')
			{
				cb->SetEnPassant(parts[3].toStdString());
			}
			else
			{
				cb->SetEnPassant("-");
			}
		}
	}
	if (PieceStorage* cps = hasPieces ? dynamic_cast<PieceStorage*>(board) : nullptr; cps != nullptr)
	{
		const QString held = !bracketed.isEmpty() ? bracketed
			: HasHoldingsField(gameVariant) && parts.size() >= 3 ? parts[2] : QString();
		cps->ClearCapturedPieces();
		int c = 0;   // 0 = no count prefix seen; Wa can hold more than 9 of a piece ("11P")
		for (k = 0; k < held.size(); k++)
		{
			if (held[k] >= '0' && held[k] <= '9')
			{
				c = c * 10 + held[k].digitValue();
			}
			else if (held[k] >= 'a' && held[k] <= 'z')
			{
				for (int index = 0; index < (c > 0 ? c : 1); index++)
				{
					PieceType pt = StringManager::StringCode2PieceType(gameVariant, uppercase(std::string(1, held[k].toLatin1())));
					if (pt != None) cps->AddCapturedPiece(pt, Black);
				}
				c = 0;
			}
			else if (held[k] >= 'A' && held[k] <= 'Z')
			{
				for (int index = 0; index < (c > 0 ? c : 1); index++)
				{
					PieceType pt = StringManager::StringCode2PieceType(gameVariant, std::string(1, held[k].toLatin1()));
					if (pt != None) cps->AddCapturedPiece(pt, White);
				}
				c = 0;
			}
		}
	}
    return "";
}

bool EngineOutputHandler::IsInsidePromotionZone(GameVariant gameVariant, PieceColour pieceColour, int y)
{
	if (gameVariant == MiniShogi)
	{
		if ((y == 4 && pieceColour == Black) ||
			(y == 0 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == JudkinShogi)
	{
		if ((y == 5 && pieceColour == Black) ||
			(y == 0 && pieceColour == White))
		{
			return true;
		}
	}
    if (gameVariant == ToriShogi)
    {
        if ((y >= 5 && pieceColour == Black) ||
            (y <= 1 && pieceColour == White))
        {
            return true;
        }
    }
    if (gameVariant == EuroShogi || gameVariant == HeianShogi)
    {
        if ((y >= 5 && pieceColour == Black) ||
            (y <= 2 && pieceColour == White))
        {
            return true;
        }
    }
    if (gameVariant == HeianDaiShogi)
    {
        if ((y >= 10 && pieceColour == Black) ||
            (y <= 2 && pieceColour == White))
        {
            return true;
        }
    }
    if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == YariShogi)
	{
		if ((y >= 6 && pieceColour == Black) ||
			(y <= 2 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == CrazyWa)
	{
		if ((y >= 8 && pieceColour == Black) ||
			(y <= 2 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == ChuShogi)
	{
		if ((y >= 8 && pieceColour == Black) ||
			(y <= 3 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == DaiShogi)
	{
		if ((y >= 10 && pieceColour == Black) ||
			(y <= 4 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == TenjikuShogi)
	{
		if ((y >= 11 && pieceColour == Black) ||
			(y <= 4 && pieceColour == White))
		{
			return true;
		}
	}
	if (gameVariant == KoShogi)
	{
		if ((y >= 13 && pieceColour == Black) ||
			(y <= 5 && pieceColour == White))
		{
			return true;
		}
	}
	return false;
}

// Which piece types have a promotion at all. Chu, Dai and Tenjiku also let a piece that is already
// standing inside the zone promote when it captures, and that second path (VBoard::CheckPromotion)
// never asked this question - which is how a Vice General, a piece with no promotion of its own, was
// offered one and svengine came back "cannot promote on this move so remove the +: a12e16+".
// The Tenjiku list is svengine's own promotion table, Data/Tenjiku.dat: those seven promote to
// nothing, while the Free King promotes to the Free Eagle and the Lion to the Lion Hawk - both of
// which used to be listed here, copied across from Chu where they really are the top of the ladder.
bool EngineOutputHandler::HasPromotion(const std::optional<Piece>& piece, GameVariant gameVariant)
{
	if (piece == std::nullopt || piece->IsPromoted) return false;
	if (gameVariant == ChuShogi || gameVariant == DaiShogi)
	{
		return piece->Type != King && piece->Type != Queen && piece->Type != Lion;
	}
	if (gameVariant == TenjikuShogi)
	{
		return piece->Type != King && piece->Type != Prince && piece->Type != LionHawk &&
		       piece->Type != ViceGeneral && piece->Type != GreatGeneral &&
		       piece->Type != FireDemon && piece->Type != FreeEagle;
	}
	return true;
}

bool EngineOutputHandler::CanBePromoted(const std::optional<Piece>& piece, GameVariant gameVariant, int oldY, int newY)
{
	if (piece != std::nullopt)
	{
        if (gameVariant == MiniShogi && !piece->IsPromoted &&
            piece->Type != King && piece->Type != Gold &&
            piece->Type != DragonKing && piece->Type != DragonHorse)
		{
            return IsInsidePromotionZone(gameVariant, piece->Colour, oldY) || IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
        if (gameVariant == JudkinShogi && !piece->IsPromoted &&
            piece->Type != King && piece->Type != Gold &&
            piece->Type != DragonKing && piece->Type != DragonHorse)
		{
            return IsInsidePromotionZone(gameVariant, piece->Colour, oldY) || IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
        if (gameVariant == ToriShogi && !piece->IsPromoted &&
            (piece->Type == Falcon || piece->Type == Pawn))
        {
            return IsInsidePromotionZone(gameVariant, piece->Colour, oldY) || IsInsidePromotionZone(gameVariant, piece->Colour, newY);
        }
        if ((gameVariant == EuroShogi || gameVariant == HeianShogi || gameVariant == HeianDaiShogi) && !piece->IsPromoted &&
            piece->Type != King && piece->Type != Gold &&
            piece->Type != DragonKing && piece->Type != DragonHorse)
        {
            return IsInsidePromotionZone(gameVariant, piece->Colour, oldY) || IsInsidePromotionZone(gameVariant, piece->Colour, newY);
        }
        if ((gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == YariShogi) && !piece->IsPromoted &&
            piece->Type != King && piece->Type != Gold &&
            piece->Type != DragonKing && piece->Type != DragonHorse)
		{
            return IsInsidePromotionZone(gameVariant, piece->Colour, oldY) || IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
        if (gameVariant == CrazyWa && !piece->IsPromoted &&
            piece->Type != King && piece->Type != CloudEagle && piece->Type != TreacherousFox)
		{
            return IsInsidePromotionZone(gameVariant, piece->Colour, oldY) || IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
        if ((gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == TenjikuShogi) && HasPromotion(piece, gameVariant))
		{
            return !IsInsidePromotionZone(gameVariant, piece->Colour, oldY) && IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
        if (gameVariant == KoShogi && !piece->IsPromoted && piece->Type != King &&
            piece->Type != Lion && piece->Type != Bishop)
		{
            return IsInsidePromotionZone(gameVariant, piece->Colour, oldY) || IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
	}
	return false;
}

// svengine emits a multi-leg move as one "move" line per leg (trailing comma on
// non-final legs) over unbuffered stdout, so the legs can land in different chunks.
// Hold the whole trailing run of "move ...," lines until the final leg arrives
// (a 3-leg move can leave two of them), or each leg would be applied and relayed
// as an independent single move.
qsizetype EngineOutputHandler::CutAtLastCompleteMove(const QByteArray& buffer)
{
    qsizetype nl = buffer.lastIndexOf('\n');
    while (nl > 0)
    {
        qsizetype end = nl;
        while (end > 0 && buffer[end - 1] == '\r') end--;
        if (end == 0) break;
        const qsizetype start = buffer.lastIndexOf('\n', end - 1) + 1;
        if (end > start && buffer[end - 1] == ',' && buffer.mid(start, 5) == "move ")
            nl = start - 1; // hold this leg too; -1 when the held run is the whole buffer
        else
            break;
    }
    return nl;
}
