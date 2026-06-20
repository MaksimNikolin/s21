import pytest
import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../ex03')))

from financial import get_field_data


def test_valid_revenue_field():
    result = get_field_data("MSFT", "Total Revenue")
    assert isinstance(result, tuple)
    assert result[0] == "Total Revenue"
    assert len(result) >= 2
    assert all(val.isdigit() for val in result[1:])

def test_return_type_is_tuple():
    result = get_field_data("AAPL", "Total Revenue")
    assert isinstance(result, tuple)

def test_invalid_ticker_raises_exception():
    with pytest.raises(Exception):
        get_field_data("INVALIDTICKER", "Total Revenue")
