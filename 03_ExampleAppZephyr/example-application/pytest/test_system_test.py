import pytest

pytestmark = pytest.mark.anyio

async def test_hello(board):
    board.wait_for_regex_in_line("Opened locker 7")

