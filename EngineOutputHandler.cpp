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

void EngineOutputHandler::CalculateCheck(Board* board, PieceColour pieceColour, std::vector<std::pair<int, int>>& moves, int oldX, int oldY, int newX, int newY)
{
	Board* brd = board->Clone();
	brd->GetMoves(board->GetData(oldX, oldY), oldX, oldY);
	brd->Move(oldX, oldY, newX, newY);
	const auto location = GetPieceLocation(board, King, pieceColour);
	const int kx = location.first;
	const int ky = location.second;
	auto opponentMoves = brd->GetAllMoves(pieceColour == White ? Black : White);
	std::for_each(opponentMoves.begin(), opponentMoves.end(), [&](std::tuple<int, int, int, int> t)
	{
		if (get<2>(t) == kx && get<3>(t) == ky)
		{
			board->RemoveMove(newX, newY);
			RemoveMove(moves, newX, newY);
		}
	});
	delete brd;
}

std::pair<int, int> EngineOutputHandler::GetPieceLocation(const Board* board, PieceType pieceType, PieceColour pieceColour)
{
	int kx = -1, ky = -1;
	for (int i = 0; i < board->GetWidth(); i++)
	{
		for (int j = 0; j < board->GetHeight(); j++)
		{
			const Piece* p = board->GetData(i, j);
			if (p != nullptr && p->GetBaseType() == pieceType && p->GetColour() == pieceColour)
			{
				kx = i;
				ky = j;
				break;
			}
		}
		if (kx > -1 && ky > -1)
			break;
	}
	return { kx, ky };
}

QByteArray EngineOutputHandler::ExtractMove(const QByteArray& buf, EngineProtocol engineProtocol, GameVariant gameVariant)
{
	const QRegularExpression _csre = QRegularExpression(R"(([a-s])(1[0-6]|[0-9])([a-s])(1[0-6]|[0-9])([+nbrq])?)");
	const QRegularExpression _cwre = QRegularExpression(R"(([PXRFSEODUGWVCLMHa-k])(@|1[0-1]|[0-9])([a-k])(1[0-1]|[0-9])([+nbrq])?)");
	const QRegularExpression _qhre = QRegularExpression(R"(([A-I])([0-9])(\-)([A-I])([0-9]))");
	const QRegularExpression _sgxbre = QRegularExpression(R"(([RBGSNLPa-o])(\*|@|[1-9])([a-o])([1-9])(\+)?)");
	const QRegularExpression _sgusre = QRegularExpression(R"(([RBGSNLP1-9])(\*|@|[a-o])([1-9])([a-o])(\+)?)");
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
					 gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
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
				QRegularExpressionMatch match = gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi
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

Move EngineOutputHandler::ByteArrayToMove(QByteArray moveArray, EngineProtocol engineProtocol, GameVariant gameVariant, int width, int height)
{
	int x1, y1, x2, y2;
	if (engineProtocol == Qianhong)
	{
		x1 = moveArray[0] - 65;
		y1 = 10 - moveArray[1];
		x2 = moveArray[2] - 65;
		y2 = 10 - moveArray[3];
	}
	else if (engineProtocol == USI)
	{
		x1 = width - moveArray[0] + 48;
		y1 = moveArray[1] - 97;
		x2 = width - moveArray[2] + 48;
		y2 = moveArray[3] - 97;
	}
	else if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == WaShogi || gameVariant == CrazyWa || gameVariant == TenjikuShogi ||
			 gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
	{
		x1 = moveArray[0] - 97;
		y1 = width - moveArray[1];
		x2 = moveArray[2] - 97;
		y2 = width - moveArray[3];
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
	textEdit->setText(engineOutput == Verbose ? buf : moveArray);
	if (moveArray.isEmpty()) return;
	const Move m = ByteArrayToMove(moveArray, engine->GetType(), gameVariant, board->GetWidth(), board->GetHeight());
	int x1 = m.x1;
	int y1 = m.y1;
	int x2 = m.x2;
	int y2 = m.y2;
	if (gameVariant == ChuShogi || gameVariant == DaiShogi || gameVariant == TenjikuShogi ||
		gameVariant == DaiDaiShogi || gameVariant == MakaDaiDaiShogi || gameVariant == KoShogi)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			if (moveArray.size() < 8)
			{
				const bool isPromoted = moveArray.size() == 5 && moveArray[4] == '+' && (y2 <= 3 || y2 >= 8);
				board->GetMoves(board->GetData(x1, y1), x1, y1);
				if (board->GetData(x2, y2) != nullptr)
				{
					delete board->GetData(x2, y2);
				}
				board->SetData(x2, y2, board->GetData(x1, y1));
				board->SetData(x1, y1, nullptr);
				AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ' ');
				engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
				if (isPromoted)
				{
					board->GetData(x2, y2)->Promote();
				}
			}
			else
			{
				const int x3 = moveArray[6] - 97;
				const int y3 = board->GetWidth() - moveArray[7];
				if (board->GetData(x2, y2) != nullptr)
				{
					delete board->GetData(x2, y2);
				}
				if (x1 != x3 || y1 != y3)
				{
					if (board->GetData(x3, y3) != nullptr)
					{
						delete board->GetData(x3, y3);
					}
					board->SetData(x3, y3, board->GetData(x1, y1));
					board->SetData(x1, y1, nullptr);
				}
				board->SetData(x2, y2, nullptr);
				AddMove(board, gameVariant, board->GetData(x3, y3)->GetType(), x1, y1, x2, y2, x3, y3);
				std::dynamic_pointer_cast<WbEngine>(engine)->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], moveArray[6], moveArray[7]);
			}
		}
	}
	else if (gameVariant == Xiangqi)
	{
		y1--;
		y2--;
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
	}
	else if (gameVariant == Chess)
	{
		// Castling check
		if ((moveArray == "e8g8" || moveArray == "e8h8" || moveArray == "e8c8" || moveArray == "e8b8" || moveArray == "e8a8" ||
			moveArray == "e1g1" || moveArray == "e1h1" || moveArray == "e1c1" || moveArray == "e1b1" || moveArray == "e1a1") &&
			board->GetData(x1, y1) != nullptr && board->GetData(x1, y1)->GetType() == King &&
			board->GetData(x2 > 4 ? 7 : 0, y2) != nullptr && board->GetData(x2 > 4 ? 7 : 0, y2)->GetType() == Rook)
		{
			Piece* rook = board->GetData(x2 > 4 ? 7 : 0, y2);
			board->SetData(x2 > 4 ? 7 : 0, y2, board->GetData(x1, y1));
			board->SetData(4, y1, rook);
			dynamic_cast<ChessBoard*>(board)->WriteCastling(x1 == 7 ? "O-O" : "O-O-O");
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
		else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = moveArray.size() == 5
				&& (y2 == 0 || y2 == board->GetHeight() - 1)
				&& board->GetData(x1, y1)->GetType() == Pawn
				&& (moveArray[4] == 'n' || moveArray[4] == 'b' || moveArray[4] == 'r' || moveArray[4] == 'q');
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType ct = board->GetData(x2, y2) != nullptr ? board->GetData(x2, y2)->GetType() : None;
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
			if (isPromoted)
			{
				switch (moveArray[4])
				{
				case 'n':
					board->GetData(x2, y2)->Promote(Knight);
					break;
				case 'b':
					board->GetData(x2, y2)->Promote(Bishop);
					break;
				case 'r':
					board->GetData(x2, y2)->Promote(Rook);
					break;
				case 'q':
					board->GetData(x2, y2)->Promote(Queen);
					break;
				default:
					break;
				}
			}
		}
	}
	else if (gameVariant == Shatranj)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = board->GetData(x1, y1)->GetType() == Pawn && (y2 == 0 || y2 == board->GetHeight() - 1);
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType ct = board->GetData(x2, y2) != nullptr ? board->GetData(x2, y2)->GetType() : None;
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
			if (isPromoted)
			{
				board->GetData(x2, y2)->Promote();
			}
		}
	}
	else if (gameVariant == Makruk)
	{
		if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = board->GetData(x1, y1)->GetType() == Pawn && (y2 <= 2 || y2 >= board->GetHeight() - 3);
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			const PieceType ct = board->GetData(x2, y2) != nullptr ? board->GetData(x2, y2)->GetType() : None;
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, ' ', ct != None ? 'x' : ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
			if (isPromoted)
			{
				board->GetData(x2, y2)->Promote();
			}
		}
	}
	else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi || gameVariant == JudkinShogi || gameVariant == WaShogi || gameVariant == CrazyWa)
	{
		if ((gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi || gameVariant == CrazyWa) && (moveArray[1] == '@' || moveArray[1] == '*'))
		{
			PieceType newPiece;
			if (gameVariant != CrazyWa)
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
			else
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
			dynamic_cast<ShogiVariantBoard*>(board)->PlacePiece(newPiece, currentPlayer, x2, y2);
			AddMove(board, gameVariant, board->GetData(x2, y2)->GetType(), moveArray[0], moveArray[1], x2, y2, ' ', ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], ' ');
		}
		else if (board->CheckPosition(x1, y1) && board->GetData(x1, y1) != nullptr)
		{
			const bool isPromoted = moveArray.size() == 5 &&
				((gameVariant == MiniShogi && (y2 == 0 || y2 == 4) && moveArray[4] == '+')
					|| (gameVariant == JudkinShogi && (y2 == 0 || y2 == 5) && moveArray[4] == '+')
					|| ((gameVariant == Shogi || gameVariant == ShoShogi) && (y2 <= 2 || y2 >= 6) && moveArray[4] == '+')
					|| ((gameVariant == WaShogi || gameVariant == CrazyWa) && (y2 <= 2 || y2 >= 8) && moveArray[4] == '+'));
			board->GetMoves(board->GetData(x1, y1), x1, y1);
			board->Move(x1, y1, x2, y2, false);
			AddMove(board, gameVariant, isPromoted ? board->GetData(x2, y2)->GetBaseType() : board->GetData(x2, y2)->GetType(), x1, y1, x2, y2, isPromoted ? moveArray[4] : ' ', ' ');
			engine->AddMove(moveArray[0], moveArray[1], moveArray[2], moveArray[3], isPromoted ? moveArray[4] : ' ');
			if (isPromoted)
			{
				board->GetData(x2, y2)->Promote();
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
	if (gameVariant == Chess || gameVariant == Shatranj)
	{
		dynamic_cast<ShatranjBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Makruk)
	{
		dynamic_cast<MakrukBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
	{
		dynamic_cast<ShogiBoard*>(board)->WriteMove(p, x1, y1, x2, y2, static_cast<char>(x3), static_cast<char>(y3) == 'x');
	}
	else if (gameVariant == Xiangqi)
	{
		dynamic_cast<XiangqiBoard*>(board)->WriteMove(p, x1, y1, x2, y2);
	}
}

template <typename T> std::basic_string<T> uppercase(const std::basic_string<T>& s)
{
	std::basic_string<T> s2 = s;
	std::transform(s2.begin(), s2.end(), s2.begin(),
		[](const T v) { return static_cast<T>(std::toupper(v)); });
	return s2;
}

template <typename T> std::basic_string<T> lowercase(const std::basic_string<T>& s)
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
	std::string promo;
	do
	{
		const char c = fen[k].toLatin1();
		if (c == '/')
		{
			k++;
			j++;
			i = 0;
		}
		if (c == '+')
		{
			k++;
			promo = "+";
		}
		else if (c >= '0' && c <= '9')
		{
			k++;
			i += c - 48;
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			std::string stringCode(1, c);
			PieceType pieceType = None;
			if (gameVariant == Chess || gameVariant == Shatranj)
			{
				pieceType = ShatranjPiece::FromStringCode(uppercase(stringCode));
			}
			else if (gameVariant == Xiangqi)
			{
				pieceType = XiangqiPiece::FromStringCode(uppercase(stringCode));
			}
			else if (gameVariant == Makruk)
			{
				pieceType = MakrukPiece::FromStringCode(uppercase(stringCode));
			}
			else if (gameVariant == Shogi || gameVariant == ShoShogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
			{
				pieceType = ShogiPiece::FromStringCode(promo + uppercase(stringCode));
			}
			else if (gameVariant == WaShogi || gameVariant == CrazyWa)
			{
				pieceType = WaShogiPiece::FromStringCode(uppercase(stringCode));
			}
			else if (gameVariant == ChuShogi)
			{
				pieceType = ChuShogiPiece::FromStringCode(uppercase(stringCode));
			}
			else if (gameVariant == DaiShogi || gameVariant == TenjikuShogi)
			{
				if (k < fen.size() - 1 && (fen[k + 1] == '\'' || fen[k + 1] == '!'))
				{
					k++;
					stringCode.push_back(fen[k].toLatin1());
				}
				if (gameVariant == DaiShogi)
				{
					pieceType = DaiShogiPiece::FromStringCode(uppercase(stringCode));
				}
				else if (gameVariant == TenjikuShogi)
				{
					pieceType = TenjikuShogiPiece::FromStringCode(uppercase(stringCode));
				}
			}
			if (pieceType == None)
			{
				return "Invalid character found in the FEN string at position " + QString::number(k);
			}
			if (j == h || i == w)
			{
				return "Invalid FEN string for this game";
			}
			Piece* piece = board->CreatePiece(pieceType, c >= 'a' && c <= 'z' ? Black : White);
			if (promo == "+")
			{
				piece->Promote();
			}
			board->SetData(i, j, piece);
			promo = "";
			k++;
			i++;
		}
	} while ((i < w || j < h - 1) && k < fen.size());
	if (gameVariant == Chess)
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
	if (gameVariant == Shogi || gameVariant == MiniShogi || gameVariant == JudkinShogi)
	{
		if (parts.size() >= 3)
		{
			ShogiVariantBoard* svb = dynamic_cast<ShogiVariantBoard*>(board);
			k = 0;
			do
			{
				if (parts[2][k] >= 'a' && parts[2][k] <= 'z')
				{
					svb->AddCapturedPiece(ShogiPiece::FromStringCode(uppercase(std::string(1, parts[2][k].toLatin1()))), Black);
				}
				else if (parts[2][k] >= 'A' && parts[2][k] <= 'Z')
				{
					svb->AddCapturedPiece(ShogiPiece::FromStringCode(std::string(1, parts[2][k].toLatin1())), White);
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
	if (gameVariant == Shogi || gameVariant == ShoShogi)
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

bool EngineOutputHandler::CanBePromoted(const Piece* piece, GameVariant gameVariant, int oldY, int newY)
{
	if (piece != nullptr)
	{
		if (gameVariant == MiniShogi && !piece->IsPromoted() &&
			piece->GetType() != King && piece->GetType() != Gold &&
			piece->GetType() != DragonKing && piece->GetType() != DragonHorse)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == JudkinShogi && !piece->IsPromoted() &&
			piece->GetType() != King && piece->GetType() != Gold &&
			piece->GetType() != DragonKing && piece->GetType() != DragonHorse)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if ((gameVariant == Shogi || gameVariant == ShoShogi) && !piece->IsPromoted() &&
			piece->GetType() != King && piece->GetType() != Gold &&
			piece->GetType() != DragonKing && piece->GetType() != DragonHorse)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if ((gameVariant == WaShogi || gameVariant == CrazyWa) && !piece->IsPromoted() &&
			piece->GetType() != King && piece->GetType() != CloudEagle && piece->GetType() != TreacherousFox)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == ChuShogi && !piece->IsPromoted() && piece->GetType() != King &&
			piece->GetType() != Queen && piece->GetType() != Lion)
		{
			return !IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) && IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == DaiShogi && !piece->IsPromoted() && piece->GetType() != King &&
			piece->GetType() != Queen && piece->GetType() != Lion)
		{
			return !IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) && IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == TenjikuShogi && !piece->IsPromoted() && piece->GetType() != King &&
			piece->GetType() != Queen && piece->GetType() != Lion && piece->GetType() != LionHawk &&
			piece->GetType() != ViceGeneral && piece->GetType() != GreatGeneral &&
			piece->GetType() != FireDemon && piece->GetType() != FreeEagle)
		{
			return !IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) && IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
		if (gameVariant == KoShogi && !piece->IsPromoted() && piece->GetType() != King &&
			piece->GetType() != Lion && piece->GetType() != Bishop)
		{
			return IsInsidePromotionZone(gameVariant, piece->GetColour(), oldY) || IsInsidePromotionZone(gameVariant, piece->GetColour(), newY);
		}
	}
	return false;
}
