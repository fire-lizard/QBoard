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
        if (piece->Type == Unicorn)
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
	std::for_each(opponentMoves.begin(), opponentMoves.end(), [&](const std::tuple<int, int, int, int>& t)
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

void EngineOutputHandler::RollbackIllegalMove(GameVariant gameVariant, Board *board, std::vector<std::string> moves)
{
    if (moves.size() > 1)
    {
        moves.pop_back();
        SetFenToBoard(board, QByteArray::fromStdString(moves[moves.size() - 1]), gameVariant);
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
    const QRegularExpression _csre = QRegularExpression(R"(([a-s])(1[0-6]|[0-9])([a-s])(1[0-6]|[0-9])([+nbrqac])?)");
    const QRegularExpression _cwre = QRegularExpression(R"(([PXRFSEODUGWVCLMHa-k])(@|1[0-1]|[0-9])([a-k])(1[0-1]|[0-9])(\+)?)");
	const QRegularExpression _qhre = QRegularExpression(R"(([A-I])([0-9])(\-)([A-I])([0-9]))");
    const QRegularExpression _sgxbre = QRegularExpression(R"(([RBGSNLPFCWKHDYa-o])(\*|@|[1-9])([a-o])([1-9])(\+)?)");
    const QRegularExpression _sgusre = QRegularExpression(R"(([RBGSNLPFCWKHDY1-9])(\*|@|[a-o])([1-9])([a-o])(\+)?)");
	QByteArray result;
	QStringList parts = QString(buf).trimmed().split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);
	for (auto& part : parts)
	{
		if (engineProtocol == XBoard ? part.startsWith("move ") : part.startsWith("bestmove "))
		{
			if (engineProtocol == USI)
			{
				QRegularExpressionMatch match = _sgusre.match(part);
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
			else if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == WaShogi || gameVariant == TenjikuShogi ||
                     gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi || gameVariant == HeianDaiShogi ||
                     gameVariant == CapablancaChess || gameVariant == GothicChess || gameVariant == JanusChess || gameVariant == GrandChess ||
                     gameVariant == OmegaChess || gameVariant == CourierChess || gameVariant == GrandeAcedrex)
			{
				QRegularExpressionMatch match = _csre.match(part);
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
			else if (gameVariant == CrazyWa)
			{
				QRegularExpressionMatch match = _cwre.match(part);
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
                QRegularExpressionMatch match = gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == MiniShogi ||
                        gameVariant == JudkinShogi || gameVariant == WhaleShogi || gameVariant == ToriShogi || gameVariant == EuroShogi || gameVariant == YariShogi ||
                        gameVariant == HeianShogi
					? _sgxbre.match(part) : _csre.match(part);
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
		}
		else if (engineProtocol == Qianhong)
		{
			QRegularExpressionMatch match = _qhre.match(part);
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
	}
	return result;
}

Move EngineOutputHandler::ByteArrayToMove(QByteArray moveArray, EngineProtocol engineProtocol, int width, int height)
{
	int x1, y1, x2, y2;
	if (engineProtocol == Qianhong)
	{
		x1 = moveArray[0] - 65;
        y1 = height - moveArray[1];
		x2 = moveArray[2] - 65;
        y2 = height - moveArray[3];
	}
	else if (engineProtocol == USI)
	{
		x1 = width - moveArray[0] + 48;
		y1 = moveArray[1] - 97;
		x2 = width - moveArray[2] + 48;
		y2 = moveArray[3] - 97;
	}
    else if (width >= 10 || (width != 9 && height >= 10))
	{
		x1 = moveArray[0] - 97;
        y1 = height - moveArray[1];
		x2 = moveArray[2] - 97;
        y2 = height - moveArray[3];
	}
    else
	{
		x1 = moveArray[0] - 97;
		y1 = height - moveArray[1] + 48;
		x2 = moveArray[2] - 97;
		y2 = height - moveArray[3] + 48;
	}
	return {x1, y1, x2, y2};
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

void EngineOutputHandler::ReadStandardOutput(const QByteArray& buf, const std::shared_ptr<Engine>& engine, Board * board, QTextEdit * textEdit,
	GameVariant gameVariant, EngineOutput engineOutput, PieceColour currentPlayer)
{
	if (engine->GetType() == XBoard)
	{
		const QString str = QString(buf);
		if (str.contains("setboard=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("setboard", false);
		if (str.contains("setboard=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("setboard", true);
		if (str.contains("memory=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("memory", false);
		if (str.contains("memory=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("memory", true);
		if (str.contains("usermove=0")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("usermove", false);
		if (str.contains("usermove=1")) std::dynamic_pointer_cast<WbEngine>(engine)->SetOption("usermove", true);
	}
	const QByteArray moveArray = ExtractMove(buf, engine->GetType(), gameVariant);
    if (std::any_of(buf.begin(), buf.end(), [=](char t) {return isprint(t);}))
    {
        textEdit->setText(engineOutput == Verbose ? buf : moveArray);
    }
	if (moveArray.isEmpty()) return;
    const Move m = ByteArrayToMove(moveArray, engine->GetType(), board->GetWidth(), board->GetHeight());
	int x1 = m.x1;
	int y1 = m.y1;
	int x2 = m.x2;
	int y2 = m.y2;
    const int ms = moveArray.size();
    if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == TenjikuShogi ||
		gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
            if (ms < 8)
			{
                const bool isPromoted = moveArray[ms - 1] == '+' && (y2 <= 3 || y2 >= 8);
				board->GetMoves(board->GetData(x1, y1), x1, y1);
				board->SetData(x2, y2, board->GetData(x1, y1));
				board->SetData(x1, y1, std::nullopt);
                AddMove(board, gameVariant, board->GetData(x2, y2)->Type, x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ', ' ');
                engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
				if (isPromoted)
				{
                    board->Promote(x2, y2);
				}
			}
			else
			{
				const int x3 = moveArray[6] - 97;
				const int y3 = board->GetWidth() - moveArray[7];
				if (x1 != x3 || y1 != y3)
				{
					board->SetData(x3, y3, board->GetData(x1, y1));
					board->SetData(x1, y1, std::nullopt);
				}
				board->SetData(x2, y2, std::nullopt);
                AddMove(board, gameVariant, board->GetData(x3, y3)->Type, x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, x3, board->GetHeight() - y3);
                std::dynamic_pointer_cast<WbEngine>(engine)->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, x3, board->GetHeight() - y3);
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
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, board->GetData(x2, y2)->Type, x1, y1, x2, y2, ' ', ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
	}
    else if (gameVariant == GrandChess)
    {
        y1--;
        y2--;
        if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
        {
            const bool isPromoted = (y2 == 0 || y2 == board->GetHeight() - 1) && board->GetData(x1, y1)->Type == Pawn &&
                (moveArray[ms - 1] == 'n' || moveArray[ms - 1] == 'b' || moveArray[ms - 1] == 'r' ||
                 moveArray[ms - 1] == 'q' || moveArray[ms - 1] == 'a' || moveArray[ms - 1] == 'c');
            board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
            board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, board->GetData(x2, y2)->Type, x1, board->GetHeight() - y1, x2, board->GetHeight() - y2,
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
        if (abs(x1 - x2) > 1 && board->GetData(x1, y1) != std::nullopt && board->GetData(x1, y1)->Type == King)
        {
            auto coords = board->FindNearestPiece(x1, y1, x1 < x2 ? East : West);
            std::optional<Piece> rook = board->GetData(coords.first, coords.second);
            board->SetData(x1 < x2 ? x1 + 2 : x1 - 2, y2, board->GetData(x1, y1));
            board->SetData(x1 < x2 ? coords.first - 3 : coords.first + 4, y1, rook);
            board->SetData(x1, y1, std::nullopt);
            board->SetData(coords.first, coords.second, std::nullopt);
            dynamic_cast<ChessBoard*>(board)->WriteCastling(x1 == board->GetWidth() - 3 ? "O-O" : "O-O-O");
            engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, ' ');
        }
        else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
        {
            const bool isPromoted = (y2 == 1 || y2 == board->GetHeight() - 2) && board->GetData(x1, y1)->Type == Pawn &&
                (moveArray[ms - 1] == 'n' || moveArray[ms - 1] == 'b' || moveArray[ms - 1] == 'r' ||
                 moveArray[ms - 1] == 'q' || moveArray[ms - 1] == 'c' || moveArray[ms - 1] == 'w');
            board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
            board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, board->GetData(x2, y2)->Type, x1, board->GetHeight() - y1, x2, board->GetHeight() - y2,
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
        }
    }
    else if (std::find(std::begin(chessVariants), std::end(chessVariants), gameVariant) != std::end(chessVariants))
	{
		// Castling check
        if (abs(x1 - x2) > 1 && board->GetData(x1, y1) != std::nullopt && board->GetData(x1, y1)->Type == King)
		{
            auto coords = board->FindNearestPiece(x1, y1, x1 < x2 ? East : West);
        	std::optional<Piece> rook = board->GetData(coords.first, coords.second);
            if (gameVariant == CapablancaChess || gameVariant == GothicChess || gameVariant == JanusChess)
            {
                board->SetData(x1 < x2 ? x1 + 4 : x1 - 3, y2, board->GetData(x1, y1));
                board->SetData(x1 < x2 ? coords.first - 2 : coords.first + 2, y1, rook);
            }
            else if (gameVariant == ChancellorChess || gameVariant == ModernChess)
            {
                board->SetData(x1 < x2 ? x1 + 2 : x1 - 2, y2, board->GetData(x1, y1));
                board->SetData(x1 < x2 ? coords.first - 3 : coords.first + 3, y1, rook);
            }
            else
            {
                board->SetData(x1 < x2 ? x1 + 2 : x1 - 2, y2, board->GetData(x1, y1));
                board->SetData(x1 < x2 ? coords.first - 2 : coords.first + 3, y1, rook);
            }
            board->SetData(x1, y1, std::nullopt);
            board->SetData(coords.first, coords.second, std::nullopt);
            dynamic_cast<ChessBoard*>(board)->WriteCastling(x1 == board->GetWidth() - 1 ? "O-O" : "O-O-O");
            engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, ' ');
		}
		else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
            const bool isPromoted = (y2 == 0 || y2 == board->GetHeight() - 1) && board->GetData(x1, y1)->Type == Pawn &&
                (moveArray[4] == 'n' || moveArray[4] == 'b' || moveArray[4] == 'r' ||
                 moveArray[4] == 'q' || moveArray[4] == 'a' || moveArray[4] == 'c');
			board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, board->GetData(x2, y2)->Type, x1, board->GetHeight() - y1, x2, board->GetHeight() - y2,
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
    else if (gameVariant == GrandeAcedrex)
    {
        if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
        {
            const bool isPromoted = (y2 == 0 || y2 == board->GetHeight() - 1) && board->GetData(x1, y1)->Type == Pawn &&
                (moveArray[ms - 1] == 'u' || moveArray[ms - 1] == 'l' || moveArray[ms - 1] == 'r' ||
                 moveArray[ms - 1] == 'g' || moveArray[ms - 1] == 'a' || moveArray[ms - 1] == 'c');
            board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
            board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, board->GetData(x2, y2)->Type, x1, board->GetHeight() - y1, x2, board->GetHeight() - y2,
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
    else if (gameVariant == Shatranj || gameVariant == Shatar || gameVariant == CourierChess)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
            const bool isPromoted = board->GetData(x1, y1)->Type == Pawn && (y2 == 0 || y2 == board->GetHeight() - 1);
			board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, board->GetData(x2, y2)->Type, x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
			if (isPromoted)
			{
                board->Promote(x2, y2);
			}
		}
	}
	else if (gameVariant == Makruk)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != std::nullopt)
		{
            const bool isPromoted = board->GetData(x1, y1)->Type == Pawn && (y2 <= 2 || y2 >= board->GetHeight() - 3);
			board->GetMoves(board->GetData(x1, y1), x1, y1);
            const PieceType ct = board->GetData(x2, y2) != std::nullopt ? board->GetData(x2, y2)->Type : None;
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, board->GetData(x2, y2)->Type, x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
			if (isPromoted)
			{
                board->Promote(x2, y2);
			}
		}
	}
    else if (gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi ||
             gameVariant == JudkinShogi || gameVariant == WhaleShogi || gameVariant == ToriShogi || gameVariant == EuroShogi || gameVariant == YariShogi ||
             gameVariant == HeianShogi || gameVariant == HeianDaiShogi || gameVariant == WaShogi || gameVariant == CrazyWa)
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
                case 'P':
                    newPiece = Pawn;
                    break;
                default:
                    newPiece = None;
                    break;
                }
            }
			dynamic_cast<ShogiVariantBoard*>(board)->PlacePiece(newPiece, currentPlayer, x2, y2);
            AddMove(board, gameVariant, board->GetData(x2, y2)->Type, moveArray[0], moveArray[1], x2, board->GetHeight() - y2, ' ', ' ');
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
            const bool isPromoted =
                ((gameVariant == MiniShogi && (y2 == 0 || y2 == 4) && moveArray[ms - 1] == '+')
                    || (gameVariant == JudkinShogi && (y2 == 0 || y2 == 5) && moveArray[ms - 1] == '+')
                    || (gameVariant == ToriShogi && (y2 <= 1 || y2 >= 5) && moveArray[ms - 1] == '+')
                    || ((gameVariant == EuroShogi || gameVariant == HeianShogi) && (y2 <= 2 || y2 >= 5) && moveArray[ms - 1] == '+')
                    || (gameVariant == HeianDaiShogi && (y2 <= 2 || y2 >= 10) && moveArray[ms - 1] == '+')
                    || ((gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == YariShogi) && (y2 <= 2 || y2 >= 6) && moveArray[ms - 1] == '+')
                    || ((gameVariant == WaShogi || gameVariant == CrazyWa) && (y2 <= 2 || y2 >= 8) && moveArray[ms - 1] == '+'));
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			board->Move(x1, y1, x2, y2, false);
            AddMove(board, gameVariant, board->GetData(x2, y2)->BaseType, x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ', ' ');
            if (engine->GetType() == USI)
            {
                engine->AddMove(board->GetWidth() - x1, y1, board->GetWidth() - x2, y2, isPromoted ? moveArray[ms - 1] : ' ');
            }
            else
            {
                engine->AddMove(x1, board->GetHeight() - y1, x2, board->GetHeight() - y2, isPromoted ? moveArray[ms - 1] : ' ');
            }
			if (isPromoted)
			{
                board->Promote(x2, y2);
            }
        }
	}
}

void EngineOutputHandler::ReadStandardError(const QByteArray& buf, QTextEdit* textEdit)
{
	textEdit->setHtml("<p style='color:red'>" + buf + "</p>");
}

void EngineOutputHandler::AddMove(Board* board, GameVariant gameVariant, PieceType p, int x1, int y1, int x2, int y2, int x3, int y3)
{
    if (std::find(std::begin(chessVariants), std::end(chessVariants), gameVariant) != std::end(chessVariants) ||
            gameVariant == Shatranj || gameVariant == Shatar)
	{
		dynamic_cast<ShatranjBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Makruk)
	{
		dynamic_cast<MakrukBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
    else if (gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == ShoShogi ||
             gameVariant == MiniShogi || gameVariant == JudkinShogi || gameVariant == EuroShogi)
	{
		dynamic_cast<ShogiBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Xiangqi)
	{
		dynamic_cast<XiangqiBoard*>(board)->WriteMove(p, x1, y1, x2, y2);
	}
}

template <typename T> static std::basic_string<T> uppercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::toupper(v)); });
	return s2;
}

template <typename T> static std::basic_string<T> lowercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::tolower(v)); });
	return s2;
}

QString EngineOutputHandler::SetFenToBoard(Board* board, const QByteArray& str, GameVariant gameVariant)
{
	QStringList parts = QString(str).trimmed().split(' ', Qt::SkipEmptyParts);
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
		if (c == '+')
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
                i += c != '0' ? 10 : 9;
                isDigit = false;
            }
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
            isDigit = false;
            std::string stringCode(1, c);
			PieceType pieceType;
            if (gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == ShoShogi ||
                gameVariant == MiniShogi || gameVariant == JudkinShogi || gameVariant == EuroShogi || gameVariant == HeianShogi ||
                gameVariant == HeianDaiShogi || gameVariant == ToriShogi || gameVariant == WaShogi || gameVariant == CrazyWa || gameVariant == ChuShogi)
			{
                pieceType = StringManager::StringCode2PieceType(gameVariant, promo + uppercase(stringCode));
			}
            else if (gameVariant == DaiShogi || gameVariant == TenjikuShogi || gameVariant == YariShogi ||
				gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
			{
				if (k < fen.size() - 1 && (fen[k + 1] == '\'' || fen[k + 1] == '!' || fen[k + 1] == '~'))
				{
					k++;
					stringCode.push_back(fen[k].toLatin1());
				}
                if (gameVariant == YariShogi)
                {
                    pieceType = StringManager::StringCode2PieceType(gameVariant, uppercase(stringCode));
                }
                else
				{
                    pieceType = StringManager::StringCode2PieceType(gameVariant, promo + uppercase(stringCode));
                }
			}
            else
            {
                pieceType = StringManager::StringCode2PieceType(gameVariant, uppercase(stringCode));
            }
            if (pieceType == None)
			{
				return "Invalid character found in the FEN string at position " + QString::number(k);
			}
			if (j == h || i == w)
			{
				return "Invalid FEN string for this game";
			}
			board->SetData(i, j, std::make_optional<Piece>(pieceType, c >= 'a' && c <= 'z' ? Black : White));
            if (promo == "+")
            {
                if (gameVariant != MicroShogi && gameVariant != KyotoShogi)
                {
                    board->Promote(i, j);
                }
            }
            promo = "";
			k++;
			i++;
		}
	} while ((i < w || j < h - 1) && k < fen.size());
    if (std::find(std::begin(chessVariants), std::end(chessVariants), gameVariant) != std::end(chessVariants))
	{
		ChessBoard* cb = dynamic_cast<ChessBoard*>(board);
		if (parts.size() >= 3)
		{
			cb->SetCastling(parts[2].toStdString());
		}
		if (parts.size() >= 4)
		{
			if (parts[3].size() == 2 && parts[3][0] >= 'a' && parts[3][0] <= 'h' && parts[3][1] >= '1' && parts[3][1] <= '8')
			{
				cb->SetEnPassant(parts[3].toStdString());
			}
			else
			{
				cb->SetEnPassant("-");
			}
		}
	}
    if (gameVariant == MicroShogi || gameVariant == KyotoShogi || gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi ||
            gameVariant == WhaleShogi || gameVariant == ToriShogi || gameVariant == EuroShogi || gameVariant == YariShogi)
	{
		if (parts.size() >= 3)
		{
			ShogiVariantBoard* svb = dynamic_cast<ShogiVariantBoard*>(board);
			k = 0;
			do
			{
				if (parts[2][k] >= 'a' && parts[2][k] <= 'z')
				{
                    svb->AddCapturedPiece(StringManager::StringCode2PieceType(gameVariant, uppercase(std::string(1, parts[2][k].toLatin1()))), Black);
				}
				else if (parts[2][k] >= 'A' && parts[2][k] <= 'Z')
				{
                    svb->AddCapturedPiece(StringManager::StringCode2PieceType(gameVariant, std::string(1, parts[2][k].toLatin1())), White);
				}
				k++;
			} while (k < parts[2].size() && ((parts[2][k] >= 'a' && parts[2][k] <= 'z') || (parts[2][k] >= 'A' && parts[2][k] <= 'Z')));
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
	if (gameVariant == WaShogi || gameVariant == CrazyWa)
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
        if ((gameVariant == WaShogi || gameVariant == CrazyWa) && !piece->IsPromoted &&
            piece->Type != King && piece->Type != CloudEagle && piece->Type != TreacherousFox)
		{
            return IsInsidePromotionZone(gameVariant, piece->Colour, oldY) || IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
        if (gameVariant == ChuShogi && !piece->IsPromoted && piece->Type != King &&
            piece->Type != Queen && piece->Type != Lion)
		{
            return !IsInsidePromotionZone(gameVariant, piece->Colour, oldY) && IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
        if (gameVariant == DaiShogi && !piece->IsPromoted && piece->Type != King &&
            piece->Type != Queen && piece->Type != Lion)
		{
            return !IsInsidePromotionZone(gameVariant, piece->Colour, oldY) && IsInsidePromotionZone(gameVariant, piece->Colour, newY);
		}
        if (gameVariant == TenjikuShogi && !piece->IsPromoted && piece->Type != King &&
            piece->Type != Queen && piece->Type != Lion && piece->Type != LionHawk &&
            piece->Type != ViceGeneral && piece->Type != GreatGeneral &&
            piece->Type != FireDemon && piece->Type != FreeEagle)
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
