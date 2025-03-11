from loguru import logger
from utils.utils import get_project_root

logger.remove()

log_directory = get_project_root() / "logs"
log_directory.mkdir(exist_ok=True)

controller_log = logger.bind(name="controller")
controller_log.add(
    log_directory / "controller.log",
    format=(
        "<green>[{time:YYYY-MM-DD HH:mm:ss}]</green> "
        "<cyan>{file}</cyan>:<cyan>{line}</cyan> "
        "<level>{level: <8}</level>: {message}"
    ),
    level="DEBUG",
    filter=lambda record: record["extra"].get("name") == "controller",
    rotation="10 MB",
    backtrace=True,
    diagnose=True,
)

presentation_log = logger.bind(name="presentation")
presentation_log.add(
    log_directory / "presentation.log",
    format=(
        "<green>[{time:YYYY-MM-DD HH:mm:ss}]</green> "
        "<cyan>{file}</cyan>:<cyan>{line}</cyan> "
        "<level>{level: <8}</level>: {message}"
    ),
    level="DEBUG",
    filter=lambda record: record["extra"].get("name") == "presentation",
    rotation="10 MB",
    backtrace=True,
    diagnose=True,
)

domain_log = logger.bind(name="domain")
domain_log.add(
    log_directory / "domain.log",
    format=(
        "<green>[{time:YYYY-MM-DD HH:mm:ss}]</green> "
        "<cyan>{file}</cyan>:<cyan>{line}</cyan> "
        "<level>{level: <8}</level>: {message}"
    ),
    level="DEBUG",
    filter=lambda record: record["extra"].get("name") == "domain",
    rotation="10 MB",
    backtrace=True,
    diagnose=True,
)
